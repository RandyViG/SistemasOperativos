#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main( int argc , char * argv[] ){
	printf("%s %d %s %d\n",argv[1],getpid(),argv[2],getppid());
	return 0;
}
