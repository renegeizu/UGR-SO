#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
        struct flock cerrojo;
        int fd;

	if(argc != 2){
                perror("Argumentos: <archivo>\n");
                return 1;
        }

        fd = open(argv[1], O_RDWR);
        if(fd == -1){
                perror("Error al Abrir el Archivo\n");
                return 1;
        }

        cerrojo.l_type = F_WRLCK;
        cerrojo.l_whence = SEEK_SET;
        cerrojo.l_start = 0;
        cerrojo.l_len = 0;
        
        printf ("Intento bloquear el Archivo\n");
        if(fcntl(fd, F_SETLKW, &cerrojo) == EDEADLK){
                perror("fcntl ha dado un EDEADLK\n");
        }
	
	printf("Archivo bloqueado con exito durante 7 segundos\n");
	int i;
       	for (i = 0; i < 7; i++){
		printf("\t Quedan %d segundos\n", 15-i);
		sleep(1);
	}	

        cerrojo.l_type = F_UNLCK;
        cerrojo.l_whence = SEEK_SET;
        cerrojo.l_start = 0;
        cerrojo.l_len = 0;

	printf("Intento desbloquear el Archivo\n");
        if (fcntl(fd, F_SETLKW, &cerrojo) == -1) {
                perror ("Error al desbloquear el archivo\n");
        }

	printf("Archivo desbloqueado con exito. Fin del programa.\n");
        
        return 0;
}
