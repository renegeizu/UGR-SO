#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	if(argc != 4){
		perror ("Argumentos: 'orden' 'redireccion <>' 'archivo'");
		return 1;
	}

	char *archivo = argv[3], *orden = argv[1], *redireccion = argv[2];
	int fd;

	if(strcmp(redireccion, ">") == 0){
		fd = open(archivo,  O_CREAT|O_WRONLY);
		close (STDOUT_FILENO);
		if(fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1){ 
			perror ("\n Fallo en fcntl");
			return 1;
		}
	}else if(strcmp(redireccion, "<") == 0){
		fd = open(archivo, O_RDONLY);
		close(STDIN_FILENO);
		if(fcntl(fd, F_DUPFD, STDIN_FILENO) == -1){
			perror ("\n Fallo en fcntl");
			return 1;
		}
	}else{
		perror ("En redireccion hay que pasar '<' o '>'");
		return 1;
	}

	if(execlp(orden, "", NULL) < 0){
		perror ("\n Fallo en execlp");
		return 1;
	}

	close(fd);
	
	return 0;
}
