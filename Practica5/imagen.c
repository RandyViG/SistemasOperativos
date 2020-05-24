#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ	0
#define WRITE	1

int main ( void ){
  	int dsDad[2],dsSon[2],bytes,pid,l,w;
  	char message[100],send[100],fileName[100],newName[100],*ok="Recibiendo",*error="error";
	FILE *f, *f1;
	struct stat st;
	long size,fRead,fWrite;

  	printf ("\t*************  Envio de Imagen *************\n");

  	pipe( dsDad );
  	pipe( dsSon );
	pid = fork();
	if( pid == -1 )
		printf("\tError al crear el proceso hijo... \n");
	else if( pid == 0 ){
    	close( dsDad[WRITE] ); /* Padre hacia el hjo */
    	close( dsSon[READ] );  /* Hijo hacia el Padre */
		memset( fileName , 0 , sizeof(fileName) );
		fRead = 0;
		bytes = read ( dsDad[READ] , message , sizeof(message) );
		char *tok = strtok(message,";");
		char *tok1 = strtok(NULL,";");
		size = atoi( tok1 );
		printf("Archivo a recibir: %s , Tamaño %ld bytes\n",tok,size);
		if( f = fopen(tok,"w") ){
			while( fRead < size ){
				memset( message , 0 , 100 );
				l = read( dsDad[READ] , message , sizeof(message) );
				if( l == -1 || !strncmp( message , error , 5 ) ){
					printf("Error al leer del PIPE\n");
					write( dsSon[WRITE] , error , strlen(error)+1 );
					break;
				}
				fRead += l;
				fwrite(message,1,l,f);
				fflush(f);
				write( dsSon[WRITE] , ok , strlen(ok)+1 );
			}
			fclose(f);
			printf("Archivo Recibido con exito(Proceso Hijo)... \n");
		}
    	close( dsSon[WRITE] );
   		close( dsDad[READ] );
  	}
  	else{
    	close( dsDad[READ] );  /* Padre hacia el hijo*/
    	close( dsSon[WRITE] ); /* Hijo  hacia el padre*/
		printf("Ingresa el nombre del archivo: \n");
		scanf(" %[^\n]s", fileName);
		if( f = fopen( fileName , "r+" )){
			if( !stat( fileName , &st ) ){
				f1= fdopen(dsDad[WRITE],"w"); 
				printf("Tam Archivo: %ld \n", st.st_size);
				size = st.st_size;
				memset( &newName , 0 , sizeof(newName) );
				fWrite = 0;
	        	sprintf( newName , "1_%s;%ld" , fileName , size );
				write( dsDad[WRITE] , newName , strlen(newName)+1 );
				fflush(f1);
				while( fWrite < size ){
					memset( send , 0 , 100);
					l = fread( send , 1 , sizeof(send) , f );
					w = write( dsDad[WRITE] , send , l );
					if( w == -1 ){
						printf("Error al escribir en el PIPE\n");
						write( dsDad[WRITE] , error , strlen(error)+1 );
						break;
					}
					fflush(f1);
					fWrite += w;
					printf("\rEnviados: %ld de %ld bytes %d %%",fWrite,size, (fWrite*100)/size );
					read( dsSon[READ] , message , sizeof(message) );
					if( !strncmp( message , error , 5 ) ){
						printf("\nError en el envio del archivo\n");
						break;
					}
				}
				printf("\n");
			}
			fclose(f);
			printf("Envio finalizado (Proceso padre)...\n");
		}
		else
			printf("Error al abrir el archivo...\n");
		wait(NULL);
    	close( dsDad[WRITE] );
    	close( dsSon[READ] );
  	}
	return 0;
}
