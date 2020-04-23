#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void arbol( int rama, int nivel );

int main( int argc, char *argv[] ){
    int nivel,pid1,i;
    if( argc < 2 ){
		printf("Uso: %s niveles",argv[1]);
        exit(1);
    }
    nivel = atoi( argv[1] );
    for(i=0; i<2; i++) { 
        pid1 = fork();
        if( pid1 == -1)
            perror("No se pudo crear el proceso...\n");
        else if( pid1 == 0 ){
            if( i == 0 ){
				printf("RAMA IZQUIERDA\n");
				printf("NIVEL %d \n",nivel);
                printf("Hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
                arbol(1, --nivel);
            }   
            if( i == 1 ){
				printf("\nRAMA DERECHA\n");
				printf("NIVEL %d \n",nivel);
                printf("Hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
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
    int i,pid1;
	if(nivel <= 0)
		return;
	printf("NIVEL %d \n",nivel);
	if( rama == 1){ //rama izquierda
		for(i=0; i<2; i++) {	 
        	pid1 = fork();
        	if( pid1 == -1)
            	perror("No se pudo crear el proceso...\n");
        	else if( pid1 == 0 ){
            	if( i == 0 ){
                	printf("Hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
                	arbol(1, --nivel);
            	}   
            	if( i == 1 ){
                	printf("Hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
                	arbol(1, --nivel);
            	}
            	else
                	exit(0);     
        	}
            else 
                wait(0);
    	}
	}
	if( rama == 2){ //rama derecha
		for(i=0; i<3; i++){ 
    	    pid1 = fork();
    	    if( pid1 == -1)
    	        perror("No se pudo crear el proceso...\n");
    	    else if( pid1 == 0 ){
    	        if( i == 0 ){
    	            printf("Hijo izquierdo mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }   
    	        if( i == 1 ){
    	            printf("Hijo central mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }
    	        if( i == 2 ){
    	            printf("Hijo derecho mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }
    	        else
    	            exit(0);
    	    }
    	    else 
    	        wait(0);
    	}
	}
}