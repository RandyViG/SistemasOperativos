#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc , char *argv[] ){
	int status,pid;
	if( ( pid=fork() ) == 0 ){
		printf("\nSoy hijo, mi pid es: %d\n", getpid());
		printf("\nMi padre tiene el pid: %d\n", getppid());
		sleep(10);
	}
	else{
		sleep(10);
		printf("\nSoy el padre, mi pid es: %d\n", getpid());
		printf("\nTengo que esperar a mi hijo: %d\n" , pid);
		wait(&status);
		printf("\nMi hijo termino con un estado: %d\n", status);
	}
	return 0;
}

