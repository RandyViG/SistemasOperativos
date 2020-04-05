#define _GNU_SOURCE
#include<sys/wait.h>
#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int printHijo( void *args );

int main( int argc, char * argv[] ){
	void *child_stack;
	char hijoDer[] = {"Yo soy el proceso Hijo Derecho y mi Id es:"};
	char hijoIzq[] = {"Yo soy el proceso Hijo Izquierdo y mi Id es:"};
	pid_t pid,pid2;

	child_stack = malloc(1024*1024);
	if ( child_stack == NULL ){
		perror("\nError al reservar memoria:");	
		exit(-1);
	}

	printf("Yo soy el proceso padre y mi Id es: %d\n",getpid());

	pid = clone( printHijo , (char*)child_stack + 1024*1024 , SIGCHLD , hijoDer );
	if ( pid < 0 ){
		perror("\nError al crear al hijo: ");
		exit(-1);
	}
	pid2 = clone( printHijo , (char*)child_stack + 1024*1024 , SIGCHLD , hijoIzq );
	if ( pid2 < 0 ){
		perror("\nError al crear al hijo: ");
		exit(-1);
	}
	wait(NULL);
	free(child_stack);
	return 0;
}

int printHijo( void *args ){
	pid_t pid;
	void *child_stack;
	child_stack = malloc(1024*1024);
	if ( child_stack == NULL ){
		perror("\nError al reservar memoria:");	
		exit(-1);
	}
	printf("%s %d y el Id de mi padre es: %d\n",args,getpid(),getppid());
	return 0;
}
