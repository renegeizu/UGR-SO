#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
        if(argc != 3) {
                printf("Argumentos:<origen> <destino>\n");
                return 1;
	}

        struct stat sb;
        int fdOrigen, fdDestino;
        char *mapOrigen, *mapDestino;

        fdOrigen = open(argv[1], O_RDONLY);
        if (fdOrigen == -1){
                perror("Error al abrir el Fichero de Origen\n");
                return 1;
        }

        if (fstat(fdOrigen, &sb) == -1){
                printf("Error al hacer stat en el Fichero de Origen\n");
                return 1;
        }

        if (!S_ISREG (sb.st_mode)){
                printf ("El Fichero de Origen no es un Archivo Regular\n");
                return 1;
        }

        umask(0);
        fdDestino = open(argv[2], O_RDWR|O_CREAT|O_EXCL, S_IRWXU);
        if (fdDestino == -1){
                perror("Error al crear el Fichero de Destino");
                return 1;
        }  

        ftruncate(fdDestino, sb.st_size);

        mapOrigen = (char*)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fdOrigen, 0);
        if(mapOrigen == MAP_FAILED){
                perror("Error en el map del Fichero de Origen");
                return 1;
        }

        mapDestino = (char*)mmap(0, sb.st_size, PROT_WRITE, MAP_SHARED, fdDestino, 0);
        if(mapDestino == MAP_FAILED){
                perror("Error en el map del Fichero de Destino");
                return 1;
        }
        
        memcpy(mapDestino, mapOrigen, sb.st_size);

        munmap(mapOrigen, sb.st_size);
        munmap(mapDestino, sb.st_size);

        close(fdOrigen);
        close(fdDestino);

        return 0;
}
