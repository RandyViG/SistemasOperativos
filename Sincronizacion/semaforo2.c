// Compilar: gcc semaforo2.c -lpthread -lrt 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define TAM_MEM 1
char *Memoria;

int CrearLigamemoria( void );
int DestruyeMemoriaCompartida( int id_Memoria , char *buffer );

int main(){
    int pid,id;
    char i,j;
    sem_t mutex;
    if( sem_init( &mutex , 1 , 1 ) == -1 ){
        printf("Error al crear el semaforo\n");
        exit(1);
    }
    //id = CrearLigamemoria();
    pid = fork();
    if( pid == -1 )
        printf("Error al crear el hijo\n");
    else if( pid == 0 ){
        id = CrearLigamemoria();
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( &mutex );
            *Memoria = j;
            printf("Produjo: %d\n",j);
            sem_post( &mutex );
            //sleep( 1 );
        }
        sem_close( &mutex );
        DestruyeMemoriaCompartida( id , Memoria );
        exit(0);
    }
    else{
        id = CrearLigamemoria();
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( &mutex );
            printf("Consumio: %d\n",*Memoria);
            sem_post( &mutex );
            //sleep( 1 );
        }
        sem_close( &mutex );
        DestruyeMemoriaCompartida( id , Memoria );
    }
    sem_destroy( &mutex );
    wait(NULL);
    return 0;
}

int CrearLigamemoria( void ){
    int key2,shmid;
    key2 = ftok("/bin/ls",3);

    //Verifica si existe la zona de memoria
    if( ( shmid = shmget( key2 , sizeof( char ) * TAM_MEM , IPC_CREAT|IPC_EXCL|0666) ) == -1 ){
        // Si existe obtiene la memoria 
        if( ( shmid = shmget( key2 , sizeof(char) * TAM_MEM , 0 ) ) == -1 ){
            perror("shmget \n");
            exit(1);
        }
        else
            printf("Se ligo a la memoria\n");
    }
    else
        printf("Creo la memoria\n");

    //Se liga a la zona de memoria compartida
    if( ( Memoria = (char*)shmat( shmid , (char*) 0 , 0 ) ) == (void*)-1 ){
        perror("shmat \n");
        exit(1);
    }

    return shmid; //Descriptos de la memoria
}

int DestruyeMemoriaCompartida( int id_Memoria , char *buffer ){
    if( id_Memoria != 0 || id_Memoria != -1 ){ //Valida si ya se destruyo
        shmdt( buffer );                       //Quita la liga hacia la memoria
        shmctl( id_Memoria , IPC_RMID , (struct shmid_ds *) NULL ); //Destruye la zona de memoria
        printf("Se destruyo la memoria\n");
    } 
    else{
        shmdt( buffer );
        printf("Se desligo la memoria\n");
    }
    
}