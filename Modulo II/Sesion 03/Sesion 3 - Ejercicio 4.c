#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int i, estado;
	pid_t PID;
	for(i = 0; i < 5; i++){
		if((PID = fork()) < 0){
			perror("Error en el fork \n");
			exit(-1);
		}
		if(PID == 0){
			printf("Soy el hijo PID = %i \n", getpid());
			exit(0);
		}
	}
	for(i = 0; i < 5; i--){
		PID = wait(&estado);
		printf("Ha finalizado mi hijo con PID = %i \n", PID);
		printf("Solo me quedan %i hijos vivos \n", (4-i));
	}
}
