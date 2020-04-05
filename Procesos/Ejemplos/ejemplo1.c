#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main( int argc, char * argv[] ){
	pid_t pid;
	if( (pid = fork()) == 0 ){
		printf("\nSoy el hijo (%d, hijo de %d)\n",getpid(),getppid());
	}
	else{
		printf("\nSoy el padre (%d, hijo de %d)",getpid(),getppid());
	}
	return 0;
}
