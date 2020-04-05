#include <stdio.h>
#include <stdlib.h>

int main( int argc , char **argv[] ){
	printf("Hola\n");
	system("ls -l");
	sleep(10);
	system("ps | grep system > salida.txt");
	printf("chau\n");
	system("cat salida.txt");
	return 0;
}
