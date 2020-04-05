#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main( int argc , char **argv[] ){
	int status, pid;
	if ( ( pid = fork() ) == 0 ){
		printf("Hola soy hijo\n");
		execl("/bin/ls","ls","-l",0);
	}
	else{
		wait(&status);
		printf("Soy el padre, se termino el listado\n");
	}
	return 0;
}
