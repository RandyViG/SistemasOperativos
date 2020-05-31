#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

#define READ	0
#define WRITE	1

void fillMatrix(int *matrix[],int nrows,int ncolumns);
void printMatrix(int *matrix[],int nrows,int ncolumns);
void allocateMemory(int *matrix[],int ncolumns ,int nrows);
void product(int *matrixA[],int *matrixB[],int *row[],int ncolumns,int start,int end);

int main( int argc , char *argv[] ){
	if( argc < 4 || atoi(argv[1]) < atoi(argv[3]) ){
		printf("Uso: %s NumFilas NumColumnas NumProcesos \n",argv[0]);
		printf("Aviso:\nEl numero de filas debe ser mayor al numero de procesos \n");
		exit(0);
	}
	srand(time(NULL));
	int rows, columns, process, range, extra, pid, i, j, start, end, Ipos=0 , Fpos=0;
	rows = atoi( argv[1] );
	columns = atoi( argv[2] );
	process  = atoi( argv[3] );
	range  = rows / process ;
	extra = rows % process ;
	end = range;
	start = 0;

	int *matrixA[rows] , *matrixB[columns], *matrixR[rows], *ds[process], *ds2[process];
	allocateMemory( ds , process , 2 );
	allocateMemory( ds2 , process , 2);
	for( i = 0 ; i < process ; i++){
		if( pipe( ds[i] ) == -1 || pipe( ds2[i] ) == -1 ){
        	printf("Error al crear el pipe\n");
        	exit( 1 );
    	}
	}

	allocateMemory( matrixA , rows , columns );
	allocateMemory( matrixB , columns , rows );
	allocateMemory( matrixR , rows , rows );
	fillMatrix( matrixA , rows , columns );
	fillMatrix( matrixB , columns , rows );
	printf("Matriz A:\n");
	printMatrix( matrixA , rows , columns );
	printf("Matriz B:\n");	
	printMatrix( matrixB , columns , rows );

	for( i=0 ; i < process ; i++ ){
		pid = fork();
		if( pid == -1 )
			printf("Error al crear el proceso %d\n",i);
		else if( pid == 0 ){
            close( ds[i][READ] ); // Child to Dad
			close( ds2[i][WRITE] ); // Dad to child
			if( i == (process -1) ){
                int *rowResult[ range + extra ];
                allocateMemory( rowResult, range + extra , rows );
                product(matrixA , matrixB , rowResult , rows , start , end+extra);
				Ipos = start;
				Fpos = end+extra;
				read( ds2[i][READ] , &j , sizeof(j) );
				write( ds[i][WRITE] , &Ipos , sizeof(Ipos) );
				write( ds[i][WRITE] , &Fpos , sizeof(Fpos) );
				for ( j = 0 ; j < range + extra ; j++)
					write( ds[i][WRITE] , rowResult[j] , rows * sizeof(int) );
            }
			else{
                int *rowResult[ range ];
                allocateMemory(rowResult, range , rows );
                product(matrixA , matrixB , rowResult , rows , start , end);
				Ipos = start;
				Fpos = end;
				read( ds2[i][READ] , &j , sizeof(j) );
				write( ds[i][WRITE] , &Ipos , sizeof(Ipos) );
				write( ds[i][WRITE] , &Fpos , sizeof(Fpos) );
				for ( j = 0 ; j < range ; j++)
					write( ds[i][WRITE] , rowResult[j] , rows * sizeof(int) );
            }
			close( ds2[i][READ] );
            close( ds[i][WRITE] );
			exit(0);
		}
		start += range;
		end += range;
	}
	int aux1, aux2;
	for( i = 0 ; i < process ; i++ ){
		close( ds[i][WRITE] );
		close( ds2[i][READ] );
	}

    for( i = 0 ; i < process ; i++){
		write( ds2[i][WRITE] , &i , sizeof(i) );
        read( ds[i][READ] , &aux1 , sizeof(aux1) );
		read( ds[i][READ] , &aux2 , sizeof(aux2) );
		for( j = aux1 ; j < aux2 ; j++)
			read( ds[i][READ] , matrixR[j] , rows * sizeof(int)  );
    }

	for ( i = 0 ; i < process ; i++){
		close( ds[i][READ] );
		close( ds2[i][WRITE] );
	}

	wait(NULL);
	printf("Resultado: \n");
	printMatrix( matrixR , rows , rows );
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
			printf("%*d ",4,matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void allocateMemory( int *matrix[] , int nrows , int ncolumns ){
	int i;
	for( i = 0 ; i < nrows ; i++)
		matrix[i] = (int *) malloc( sizeof(int) * ncolumns );
}

void product( int *matrixA[], int *matrixB[] , int *row[] , int ncolumns , int start , int end ){
	int i, j, k, p , n, val;
	for( i = start , k = 0 ; i < end ; i++ , k++ ){
		for( n = 0 ; n < ncolumns ; n++ ){
			val = 0;
			for( j = 0 ; j < ncolumns ; j++ )
				val += matrixA[i][j] * matrixB[j][n]; 
			row[k][n] = val;
		}
	}
}