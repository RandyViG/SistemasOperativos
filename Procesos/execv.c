#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){

	pid_t pid,pid2;
	int status,status2;
	char *args1[] = {"usr/bin/ping","-c","5","www.google.com",NULL};
	char *args2[] = {"usr/bin/ping","-c","5","www.facebook.com",NULL};
	pid = fork();
	if( pid == -1){
		perror("Error al crear el proceso hijo: \n");
		exit(-1);
	}
	else if( pid == 0){
		printf("\n\nPing a www.google.com\n");
		printf("\nSoy el hijo %d, hijo de %d\n",getpid(),getppid());
		execv("/usr/bin/ping", args1);
		printf("Error al hacer ping a www.google.com\n");
	}
	else{
		waitpid(pid,&status,0);
		printf("\n\nPing a www.facebook.com\n");
		printf("\nSoy el padre %d\n",getpid());
		printf("Mi hijo %d termino con estatus: %d\n",pid,status);
		execv("/usr/bin/ping",args2);
		printf("Error al hacer ping a www.facebook.com\n");
	}
	return 0;
}

