// Tubería sin nombre entre procesos padre e hijo
// Comunicación de padre a hijo y de hijo a padre

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ	0
#define WRITE	1

int main ( void ){
  	int dsDad[2],dsSon[2];
  	int  bytesDad,bytesSon,pid;
  	char message[100],send[100];
  	printf ("Ejemplo comunicación entre proceso padre e hijo.\n");

	// Creando pipes
  	pipe( dsDad );
  	pipe( dsSon );
	pid = fork();
	if( pid == -1 )
		printf("Error al crear el proceso hijo... \n");
	else if (pid == 0){
		//Configurando PIPES
    		close( dsDad[WRITE] ); // PIPE del papa al hijo
    		close( dsSon[READ] ); // PIPE del hijo al papa

    		bytesDad = read ( dsDad[READ], message , 100);
    		printf("El hijo recibio: %s , %d bytes\n", message, bytesDad);
    		
    		printf("Escribe el mensaje hacia el padre:\n");
    		scanf("%[^\n]s", send);
    		write( dsSon[WRITE], send, strlen(send));

    		//Cerrando pipes
    		close( dsSon[WRITE] );
   		close( dsDad[READ] );
  	}
  	else{
    		//Configurando PIPES
    		close( dsDad[READ] ); //PIPE del papa al hijo
    		close( dsSon[WRITE] ); //PIPE del hijo al papa

    		printf("Escribe el mensaje hacia el hijo:\n");
    		scanf("%[^\n]s", send);;
    		write( dsDad[WRITE],send , strlen(send));
 
    		bytesSon = read(dsSon[READ], message, 100);
    		printf("El padre recibio: %s, %d bytes\n",message , bytesSon);

    		//Cerrando PIPES
    		close( dsDad[WRITE] );
    		close( dsSon[READ] );
  	}
	return 0;
}
