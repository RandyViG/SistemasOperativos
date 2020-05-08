/* Mini chat entre procesos utilizando PIPES con nombre 
 *  Receptor - Emisor
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    FILE *mipipe;
    char buffer[128],buffer2[128];
    char *fin = "fin";

    printf ("\t*************  C H A T *************\n");

    while( 1 ) {
        memset( buffer , 0 , 128 );
  		memset( buffer2 , 0 , 128 );
        mipipe=fopen("pipetest", "r");
        if (fgets(buffer, 128, mipipe))
            printf ("Recibido: %s\n", buffer);
        fclose(mipipe);
        if( strncmp( buffer , fin , 3 ) == 0 )
            break;
        mipipe=fopen("pipetest", "w");
        printf("Ingresa un mensaje: ");
        scanf(" %[^\n]s", buffer2);
        fputs(buffer2, mipipe);
        fclose(mipipe);
        printf("\n");
        if( strncmp( buffer2 , fin , 3 ) == 0 )
            break;
    }
    printf("\tChat finalizado... \n");
    return 0;
}