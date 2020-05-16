#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void fillMatrix(int *matrix[],int nrows,int ncolumns);
void printMatrix(int *matrix[],int nrows,int ncolumns);
void allocateMemory(int *matrix[],int ncolumns ,int nrows);
void product(int *matrixA[],int *matrixB[],int nrows,int ncolumns,int start,int end);

int main( int argc , char *argv[] ){
	if( argc < 4 || atoi(argv[1]) < atoi(argv[3]) ){
		printf("Uso: %s NumFilas NumColumnas NumProcesos \n",argv[0]);
		printf("Aviso:\nEl numero de filas debe ser mayor al numero de procesos \n");
		exit(0);
	}
	srand(time(NULL));
	int rows, columns, process, range, extra, pid, i, j, start, end;
	rows = atoi( argv[1] );
	columns = atoi( argv[2] );
	process  = atoi( argv[3] );
	range  = rows / process ;
	extra = rows % process ;
	end = range;
	start = 0;
	int *matrixA[rows] , *matrixB[columns];
	allocateMemory( matrixA , rows , columns );
	allocateMemory( matrixB , columns , rows );
	fillMatrix( matrixA , rows , columns );
	fillMatrix( matrixB , columns , rows );
	printf("Matrix A:\n");
	printMatrix( matrixA , rows , columns );
	printf("Matrix B:\n");	
	printMatrix( matrixB , columns , rows );

	for( i=0 ; i < process ; i++ ){
		pid = fork();
		if( pid == -1 )
			printf("Error al crear el proceso %d",i);
		else if( pid == 0 ){
			if( i == (process -1) )
				product(matrixA , matrixB , rows , columns , start , end+extra);
			else
				product(matrixA , matrixB , rows , columns , start , end);
			exit(0);
		}
		start += range;
		end += range;
	}
	wait(NULL);
	return 0;
}

void fillMatrix( int *matrix[] , int nrows , int ncolumns ){
	int i,j,num;
	for( i=0 ; i < nrows ; i++  )
		for( j=0 ; j < ncolumns ; j++ ){
			num = rand()%10;
			matrix[i][j]=num;
		}
}

void printMatrix( int *matrix[] , int nrows , int ncolumns ){
	int i,j,num;
	for( i=0 ; i < nrows ; i++ ){
		for( j=0 ; j < ncolumns ; j++ )
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void allocateMemory( int *matrix[] , int nrows , int ncolumns ){
	int i;
	for( i = 0 ; i < nrows ; i++)
		matrix[i] = (int *) malloc( sizeof(int) * ncolumns );
}

void product( int *matrixA[], int *matrixB[] , int nrows , int ncolumns , int start , int end ){
	int i, j, k, p, n,  val, row[ncolumns];
	printf("Proceso\n");
	for( i = start ; i < end ; i++ ){
		for( n = 0 , p = 0 ; n < ncolumns ; n++ , p++){
			val = 0;
			for( j = 0 , k = 0; j < ncolumns ; j++ , k++ ){
				val += matrixA[i][j] * matrixB[n][i];
				row[p] = val; 
			}
		}
		printf("Fila %d:  ", i);
		for( k = 0 ; k < ncolumns ; k++)
			printf("%d " , row[k]);
		printf("\n");	
	}
}