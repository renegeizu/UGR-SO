//gcc Maestro.c -o Maestro

#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
	int fd1[2], fd2[2];
	char inicio[10], fin[10];
	pid_t esclavo1, esclavo2;
	if(argc != 3){
		perror("Introduce el inicio y final del intervalo");
		exit(-1);
	}
	pipe(fd1);
	pipe(fd2);
	printf("\nNúmeros primos en el intervalo [%d, %d]:\n", atoi(argv[1]),
	atoi(argv[2]));
	esclavo1 = fork();
	sprintf(inicio, "%d", atoi(argv[1]));
	sprintf(fin, "%d", ((atoi(argv[2]) + atoi(argv[1]))/2) - 1);
	if(esclavo1 == 0){
		close(fd1[0]);
		dup2(fd1[1],STDOUT_FILENO);
		if(execl("./Esclavo", "Esclavo", inicio, fin, NULL) < 0) {
			perror("\nError en execl");
			exit(-1);
		}
	}else{
		int valor, bytes;
		close(fd1[1]);
		while((bytes = read(fd1[0],&valor, sizeof(int))) > 0){
			printf("%d \n", valor);
		}
		close(fd1[0]);
	}
	esclavo2 = fork();
	sprintf(inicio, "%d", (atoi(argv[2]) + atoi(argv[1]))/2);
	sprintf(fin, "%d", atoi(argv[2]));
	if(esclavo2 == 0){
		close(fd2[0]);
		dup2(fd2[1],STDOUT_FILENO);
		if(execl("./Esclavo", "Esclavo", inicio, fin, NULL) < 0) {
			perror("\nError en execl");
			exit(-1);
		}
	}else{
		int valor, bytes;
		close(fd2[1]);
		while((bytes = read(fd2[0], &valor, sizeof(int))) > 0){
			printf("%d \n", valor);
		}
		close(fd2[0]);
	}
	return 0;
}
