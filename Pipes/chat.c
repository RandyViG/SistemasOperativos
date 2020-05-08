/* Mini chat entre proceso padre e hijo  utilizando PIPES sin nombre */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ	0
#define WRITE	1

int main ( void ){
  	int dsDad[2],dsSon[2];
  	int  bytes,pid;
  	char message[100],send[100],*end="fin" ;
  	printf ("\t*************  C H A T *************\n");

  	pipe( dsDad );
  	pipe( dsSon );
	pid = fork();
	if( pid == -1 )
		printf("\tError al crear el proceso hijo... \n");
	else if (pid == 0){
    	close( dsDad[WRITE] ); /* Padre hacia el hjo */
    	close( dsSon[READ] );  /* Hijo hacia el Padre */
		while( 1 ){
			memset( message , 0 , 100 );
			memset( send , 0 , 100);
			bytes = read ( dsDad[READ], message , 100);
			if( strncmp( end , message, 3 ) == 0 )
				break;
 			printf("El hijo recibio: %s , %d bytes\n\n", message, bytes);
   
    		printf("Mensaje hacia el padre: ");
    		scanf(" %[^\n]s", send);
    		write( dsSon[WRITE], send, strlen(send));
			if( strncmp( end , send, 3 ) == 0 )
				break;
		}
		printf("\tChat finalizado (Proceso Hijo)... \n");
    	close( dsSon[WRITE] );
   		close( dsDad[READ] );
  	}
  	else{
    	close( dsDad[READ] );  /* Padre hacia el hijo*/
    	close( dsSon[WRITE] ); /* Hijo  hacia el padre*/
		while( 1 ){
			memset( message , 0 , 100 );
			memset( send , 0 , 100);
    		printf("Mensaje hacia el hijo: ");
    		scanf(" %[^\n]s", send);
    		write( dsDad[WRITE],send , strlen(send));
			if( strncmp( end , send , 3 ) == 0 )
				break;

    		bytes = read(dsSon[READ], message, 100);
			if( strncmp( end , message , 3 ) == 0 )
				break;
    			printf("El padre recibio: %s, %d bytes\n\n",message , bytes);
		}
		printf("\tChat finalizado (Proceso padre)...\n");
    	close( dsDad[WRITE] );
    	close( dsSon[READ] );
  	}
	return 0;
}
