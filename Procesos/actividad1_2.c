#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){

	pid_t pid,pid2;
	char hijo[] = {"Yo soy el proceso Hijo y mi Id es:"};
	char papaHijo[] = {" y el ID de mi padre es:"};
	char nieto[] = {"Yo soy el proceso Nieto y mi Id es:"};
	
	system("gcc print.c -o print");

	pid = fork();
	if( pid == -1 )
		perror("Error al crear el proceso hijo: \n");
	else if( pid == 0){
		pid2 = fork();
		if( pid2 == -1  )
			perror("Error al crear el proceso Nieto \n");
		else if( pid2 == 0 )
			execl("./print","print",nieto,papaHijo,NULL);
		else{
			wait(NULL);
			execl("./print","print",hijo,papaHijo,NULL);
		}
	}
	else{	
		wait(NULL);
		printf("Yo soy el proceso Padre y mi Id es: %d\n",getpid());
	}
	return 0;
}
