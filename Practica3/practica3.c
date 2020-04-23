#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void arbol( int rama, int nivel );

int main( int argc, char *argv[] ){

    if( argc < 2 ){
	printf("Uso: %s niveles " ,argv[0]);
        exit(1);
    }
	int nivel,pid,i;
    nivel = atoi( argv[1] );

    for(i=0; i<2; i++) { 
        pid = fork();
        if( pid == -1)
            perror("No se pudo crear el proceso...\n");
        else if( pid == 0 )
        {
            if( i == 0 ){
				printf("Rama Derecha\n");
                printf("Soy el hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
                arbol(1, --nivel);
            }   
            if( i == 1 ){
				printf("Rama Izquierda\n");
                printf("Soy el hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
                arbol(2, --nivel);
            }
            else
                exit(0);
        }
        else 
            wait(0);
    }
    return 0;
}


void arbol( int rama, int nivel ){
    printf("NIVEL %d \n",nivel+1);
    int i,pid;
	if(nivel == 0)
		return;
	if( rama == 1){ //rama izquierda
		for( i=0; i<2; i++ ){ 
        	pid = fork();
        	if( pid == -1)
            	perror("No se pudo crear el proceso...\n");
        	else if( pid == 0 ){
            	if( i == 0 ){
            		printf("Hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
            		arbol( 1, --nivel );
            	}   
            	else if( i == 1 ){
                	printf("Hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
                	arbol( 1, --nivel );
            	}
            	else
                	exit(0);
        		}
            else 
            	wait(0);
    	}
	}	
	if( rama == 2){ //rama derecha
		for( i=0 ; i<3 ; i++ ){ 
        	pid = fork();
	       	if( pid == -1)
           		perror("No se pudo crear el proceso...\n");
        	else if( pid == 0 ){
           		if( i == 0 ){
            		printf("Hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
            		arbol( 2, --nivel );
           		}   
				else if( i == 1 ){
            		printf("Hijo central mi id es %d y mi padres es %d\n", getpid(), getppid());
            		arbol( 2, --nivel );
           		}
           		else if( i == 2 ){
            		printf("Hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
            		arbol( 2, --nivel );
           		}
           		else
            		exit(0);     
        	}
           	else 
      	    	wait(0);
    	}
	}
}
