#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc , char *argv[] ){
	char *args[] = { "/bin/ls", "-la" , NULL };
	execv("/bin/ls",args);
	printf("Se ha producido un error al ejecutar execv.\n");
	return 0;
}

