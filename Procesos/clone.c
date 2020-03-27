#define _GNU_SOURCE
#include<sys/wait.h>
#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int val = 50;

int incrementarVal( void * arg );
int decrementarVal( int n );

int main( int argc, char * argv[] ){
	void *child_stack;
	pid_t pid;
	int status;

	if( argc < 2){
		printf("Uso: %s num",argv[0] );
		exit(-1);
	}

	child_stack = malloc(1024*1024);
	if ( child_stack == NULL ){
		perror("\nError al reservar memoria:");	
		exit(-1);
	}
	pid = clone( incrementarVal, (char*)child_stack + 1024*1024 , SIGCHLD ,  argv[1] );
	if ( pid < 0 ){
		perror("\nError al crear al hijo: ");
		exit(-1);
	}
	waitpid(pid,&status,0);
	printf("\nEl hijo %d termino con status %d",pid,status);
	decrementarVal( atoi( argv[1] ) );
	free(child_stack);
	return 0;
}

int incrementarVal( void * arg ){
	printf("\nFuncion ejecutada por el hijo\n");
	int i,n;
	n = atoi(arg);
	for ( i = 0; i < n ; i++)
		printf("%d\n",++val );
	return 0;
}

int decrementarVal( int n ){
	printf("\nFuncion ejecutada por el padre\n");
	int i;
	for ( i = 0; i < n ; i++)
		printf("Nuevo valor %d\n",--val); 
	return 0;
}
