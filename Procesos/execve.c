#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char * argv[] ){
	
	pid_t pid,pid2;
	int status,status2;
	char *args1[] = {"mkdir","Backup",NULL};
	char *args2[] = {"cp","fork.c","execv.c","execve.c","clone.c","Backup",NULL};
	char *args3[] = {"tar","-czvf","Backup.tar.gz","Backup",NULL};
	char *env[] = {"PATH=/etc:/tmp:/usr/bin/:/usr/local/bin:/usr/local/sbin:.",NULL};
	
	pid = fork();
	if( pid == -1){
		perror("Error al crear el proceso hijo: \n");
		exit(-1);
	}
	else if( pid == 0){
		printf("Soy el hijo %d, hijo de %d\n",getpid(),getppid());
		pid2 = fork();
		if( pid2 == -1 ){
			perror("Error al crear el proceso hijo: \n");
			exit(-1);
		}
		else if( pid2 == 0){
			printf("Soy el hijo %d, hijo de %d\n",getpid(),getppid());
			execve("/usr/bin/mkdir",args1,env);
		}
		else{
			waitpid(pid2,&status2,0);
			printf("Soy el padre %d\n",getpid());
			printf("Mi hijo %d termino con estatus: %d\n",pid2,status2);
			execve("/usr/bin/cp",args2,env);
		}
	}
	else{
		waitpid(pid,&status,0);
		printf("Soy el padre %d\n",getpid());
		printf("Mi hijo %d termino con estatus: %d\n",pid,status);
		execve("/usr/bin/tar",args3,env);
	}
	return 0;
}

