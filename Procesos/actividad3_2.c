#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){
	
	int pid,pid2,pid3,pid4;

	char hijoIzq[] = { "Yo soy el proceso Hijo Izquierdo y mi Id es:" };
	char hijoDer[] = { "Yo soy el proceso Hijo Dereccho y mi Id es:" };
	char nietoIzq[] = { "Yo soy el proceso Nieto Izquiero y mi Id es" };
	char nietoDer[] = { "Yo soy el proceso Nieto Derecho y mi Id es" };
	char hijoPapa[] = { "y el Id de mi padre es:" };
	
	system("gcc print.c -o print");
	pid = fork();
	if( pid == -1)
		perror("Error al crear el proceso hijo derecho \n");
	else if( pid == 0){
		pid2 = fork();
		if( pid2 == -1 )
			perror("Error al crear el proceso nieto izquierdo\n");
		if( pid2 == 0 )
			execl("./print","print",nietoIzq,hijoPapa,NULL);
		else{
			wait(NULL);
			execl("./print","print",hijoIzq,hijoPapa,NULL);
		}
	}
	else{
		pid3 = fork();
		if( pid3 == 0 ){
			pid4 = fork();
			if( pid4 == -1 )
				printf("Error al crear el proceso nieto derecho\n");)
			if( pid4 == 0 )
				execl("./print","print",nietoDer,hijoPapa,NULL);
			else{
				wait(NULL);
				execl("./print","print",hijoDer,hijoPapa,NULL);
			}
		}
		wait(NULL);
		printf("Yo soy el proceso padre y mi ID es: %d\n",getpid());
	}
	return 0;
}

