#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){
	
	int pid,pid2,pid3,pid4;
	pid = fork();
	if( pid == -1)
		perror("Error al crear el proceso hijo derecho \n");
	else if( pid == 0){
		printf("Yo soy el proceso hijo izquierdo y mi ID es: %d y el ID de mi padre es: %d\n",getpid(),getppid());
		pid2 = fork();
		if( pid2 == -1 )
			perror("Error al crear el proceso Nieto izquiero\n");
		if( pid2 == 0 )
			printf("Yo soy el proceso Nieto izquierdo y mi ID es: %d y el ID de mi padre es %d\n",getpid(),getppid());
		else
			wait(NULL);	
	}
	else{
		printf("Yo soy el proceso padre y mi ID es: %d\n",getpid());
		pid3 = fork();
		if( pid3 == 0 ){
			printf("Yo soy el proceso hijo derecho y mi ID es: %d y el ID de mi padre es %d\n",getpid(),getppid());
			pid4 = fork();
			if( pid4 == -1 )
				printf("Error al crear el proceso Nieto derecho\n");
			if( pid4 == 0 )
				printf("Yo soy el proceso Nieto derecho y mi ID es: %d y el ID de mi padre es %d\n",getpid(),getppid());
			else
				wait(NULL);
		}
		wait(NULL);
	}
	return 0;
}

