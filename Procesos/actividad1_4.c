#define _GNU_SOURCE
#include<sys/wait.h>
#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int printHijo( void *args );
int printNieto( void *args );

int main( int argc, char * argv[] ){
	void *child_stack;
	char hijo[] = {"Yo soy el proceso Hijo y mi Id es:"};
	pid_t pid;

	child_stack = malloc(1024*1024);
	if ( child_stack == NULL ){
		perror("\nError al reservar memoria:");	
		exit(-1);
	}

	printf("Yo soy el proceso padre y mi Id es: %d\n",getpid());

	pid = clone( printHijo , (char*)child_stack + 1024*1024 , SIGCHLD , hijo );
	if ( pid < 0 ){
		perror("\nError al crear al hijo: ");
		exit(-1);
	}
	waitpid(pid,NULL,0);
	free(child_stack);
	return 0;
}

int printHijo( void *args ){
	pid_t pid;
	void *child_stack;
	char nieto[] = {"Yo soy el proceso Nieto y mi Id es:"};
	child_stack = malloc(1024*1024);
	if ( child_stack == NULL ){
		perror("\nError al reservar memoria:");	
		exit(-1);
	}
	printf("%s %d y el Id de mi padre es: %d\n",args,getpid(),getppid());
	pid = clone( printNieto , (char*)child_stack + 1024*1024 , SIGCHLD , nieto );
	waitpid(pid,NULL,0);
	return 0;
}

int printNieto( void *args ){
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
