#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){
	
	pid_t pid,pid2;

	char *hijoDer[] = {"print","Yo soy el proceso Hijo Derecho y mi Id es:","y el Id de mi padre es:",NULL};
	char *hijoIzq[] = {"print","Yo soy el proceso Hijo Izquierdo y mi Id es:","y el Id de mi padre es:",NULL};
	char *env[] = {"PATH=/etc:/tmp:/usr/bin/:/usr/local/bin:/usr/local/sbin:.",NULL};
	
	system("gcc print.c -o print");

	pid = fork();
	if( pid == -1)
		perror("Error al crear el proceso hijo derecho \n");
	else if( pid == 0)
		execve("./print",hijoDer,env);
	else{
		printf("Yo soy el proceso padre y mi ID es: %d\n",getpid());
		wait(NULL);
		pid2 = fork();
		if( pid2 == -1)
			perror("Error al crear el proceso hijo izquierdo\n");
		else if( pid2 == 0 )
			execve("./print",hijoIzq,env);
		else
			wait(NULL);
	}
	return 0;
}
