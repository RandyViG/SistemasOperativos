// Tubería sin nombre entre procesos padre e hijo

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define READ 0
#define WRITE 1

int main( void ){
	int descr[2];
	int bytes;
	char message[100],
	     *m = "Enviando mensaje desde el proceso hijo\0\n";
	pipe(descr);
	if( fork()== 0 ){
		close( descr[READ]  );
		write( descr[WRITE] , m, strlen(m) );
		close( descr[WRITE] );
	}
	else{
		close( descr[WRITE] );
		bytes = read( descr[READ] , message, 100);
		printf( "Mensaje: %s, %d bytes\n", message , bytes);
		close( descr[READ] );
	}
	return 0;
}

