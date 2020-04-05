#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){
	
	pid_t pid,pid2;

	pid = fork();
	if( pid == -1)
		perror("Error al crear el proceso hijo derecho \n");
	else if( pid == 0)
		printf("Yo soy el proceso Hijo derecho y mi ID es: %d y el ID de mi padre es %d\n",getpid(),getppid());
	else{
		wait(NULL);
		pid2 = fork();
		if( pid2 == -1)
			perror("Error al crear el proceso hijo izquierdo\n");
		else if( pid2 == 0 )
			printf("Yo soy el proceso Hijo izquierdo y mi ID es: %d y el ID de mi padre es %d\n",getpid(),getppid());
		else{
			wait(NULL);
			printf("Yo soy el proceso padre y mi ID es: %d\n",getpid());
		}
	}
	return 0;
}

