#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int val = 50;

void incrementaValor( int n );
void decrementaValor( int n );

int main( int argc, char * argv[] ){
	if( argc < 2){
		printf("Uso: %s num\n",argv[0]);
		exit(-1);
	}
	
	pid_t pid;
	int status;

	pid = fork();
	if( pid == -1){
		perror("Error al crear el proceso hijo: \n");
	}
	else if( pid == 0){
		printf("Soy el hijo %d, hijo de %d\n",getpid(),getppid());
		incrementaValor( atoi( argv[1] ) );
		printf("Nuevo valor de val: %d\n", val);
	}
	else{
		waitpid(pid,&status,0);
		printf("Soy el padre %d\n",getpid());
		printf("Mi hijo %d termino con estatus: %d\n",pid,status);
		decrementaValor( atoi( argv[1]) );
		printf("Nuevo valor de val: %d\n", val);
	}
	return 0;
}

void incrementaValor( int n ){
	int i;
	for ( i = 0 ; i < n ; i++ )
		val += 1;
}

void decrementaValor( int n ){
	int i;
	for ( i = 0 ; i < n ; i++ )
		val -= 1;
}

