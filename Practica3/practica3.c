#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void arbol( int rama, int nivel );

int main( int argc, char *argv[] ){
    int nivel,i;
	pid_t pid1;
    if( argc < 2 ){
		printf("Uso: %s niveles\n",argv[0]);
        exit(1);
    }
    nivel = atoi( argv[1] );
    for(i=0; i<2; i++) { 
        pid1 = fork();
        if( pid1 == -1)
            perror("Error!\n No se pudo crear el proceso: \n");
        else if( pid1 == 0 ){
            if( i == 0 ){
                printf("Rama izquierda mi id es %d y mi padres es %d\n", getpid(), getppid());
                arbol(1, --nivel);
            }   
            if( i == 1 ){
                printf("Rama derecha mi id es %d y mi padres es %d\n", getpid(), getppid());
                arbol(2, --nivel);
            }
            else
                exit(0);   
        }
    }
	wait(NULL);
    return 0;
}


void arbol( int rama, int nivel ){
    int i;
	pid_t pid1;
	if(nivel <= 0)
		return;
	if( rama == 1){ //rama izquierda
		for(i=0; i<2; i++){	 
        	pid1 = fork();
        	if( pid1 == -1)
            	perror("No se pudo crear el proceso...\n");
        	else if( pid1 == 0 ){
            	if( i == 0 ){
                	printf("Hijo izquierdo de rama izquierda mi id es %d y mi padres es %d\n", getpid(), getppid());
                	arbol(1, --nivel);
            	}   
            	if( i == 1 ){
                	printf("Hijo derecho de rama izquierda mi id es %d y mi padres es %d\n", getpid(), getppid());
                	arbol(1, --nivel);
            	}
            	else
                	exit(0);     
        	}
    	}
		wait(NULL);
	}
	if( rama == 2){ //rama derecha
		for(i=0; i<3; i++){ 
    	    pid1 = fork();
    	    if( pid1 == -1)
    	        perror("No se pudo crear el proceso...\n");
    	    else if( pid1 == 0 ){
    	        if( i == 0 ){
    	            printf("Hijo izquierdo de rama derecha mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }   
    	        if( i == 1 ){
    	            printf("Hijo central de rama derecha mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }
    	        if( i == 2 ){
    	            printf("Hijo derecho de rama derecha mi id es %d y mi padres es %d\n", getpid(), getppid());
    	            arbol(2, --nivel);
    	        }
    	        else
    	            exit(0);
    	    }
    	}
		wait(NULL);
	}
}