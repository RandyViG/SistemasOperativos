// Compilar: gcc semaforo1.c -lpthread -lrt 
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
char *name = "mutex";

int CrearLigamemoria( void );
int DestruyeMemoriaCompartida( int id_Memoria , char *buffer );

int main(){
    int pid,id,val;
    char j;
    sem_t *mutex , *mutex2;

    mutex = sem_open( name , O_CREAT | O_EXCL , 0666 , 1 );
    CrearLigamemoria();

    pid = fork();
    if( pid == -1 )
        printf("Error al crear el hijo\n");
    else if( pid == 0 ){
        //id = CrearLigamemoria();
        mutex2 = sem_open( name , 0 );
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( mutex2 );
            *Memoria = j;
            printf("Produjo: %d\n",j);
            sem_post( mutex2 );
            //sleep(1);
        }
        sem_close( mutex2 );
        DestruyeMemoriaCompartida( id , Memoria );
        exit(0);
    }
    else{
        //id = CrearLigamemoria();
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( mutex );
            printf("consumio: %d\n",*Memoria);
            sem_post( mutex );
            //sleep(1);
        }
        DestruyeMemoriaCompartida( id , Memoria );
    }
    wait(NULL);
    sem_close( mutex );
    sem_unlink( name );
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