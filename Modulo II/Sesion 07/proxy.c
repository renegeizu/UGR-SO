#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void bloquear(int dbloqueo, int flag){
	struct flock cerrojo;
	cerrojo.l_type = flag;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if(fcntl(dbloqueo, F_SETLKW, &cerrojo) < -1){
		perror ("Proxy: Error en bloquear\n");
		return -1;
	}
}

int main(int argc, char *argv[]){
	char buffer[1024], fifoproxy[256];
	int bytes, dbloqueo;
	FILE *temporal = tmpfile();
	while((bytes = read(STDIN_FILENO, buffer, 1024)) > 0){
		if(fwrite(buffer, sizeof(char), bytes, temporal) < 0){
			perror("Error en fwrite");
			return -1;
		}
	}
	if ((dbloqueo = open("bloqueo", O_RDWR | O_CREAT)) < 0){
		printf("Error al abrir bloqueo\n");
	}
	bloquear(dbloqueo, F_WRLCK);
	while(fread(buffer, sizeof(char), 1024, temporal) > 0){
		if(write(STDOUT_FILENO, buffer, 1024) < 0){
			perror("Error en write");
			return -1;
		}
	}
	bloquear(dbloqueo, F_UNLCK);
	sprintf(fifoproxy,"fifo.%d", getpid());
	unlink(fifoproxy);
	return 0;
}
