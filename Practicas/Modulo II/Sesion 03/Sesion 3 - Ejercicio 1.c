#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		perror("\nError en el numero de parametros");
		exit(-1);
	}
	int numero = atoi(argv[1]);
	pid_t pid;
	pid = fork();
	if (pid < 0){
		perror("\nError en el fork");
		exit(-1);
	}else if (pid == 0){
		printf("Proceso Hijo -- PID: %d - PPID: %d \n", getpid(), getppid());
		if ((numero % 2) == 0)
			printf("El numero %d introducido es par \n", numero);
		else 
			printf("El numero %d introducido es impar \n", numero);
	}else{
		printf("Proceso Padre -- PID: %d - PID Hijo: %d \n", getpid(), pid);
		if (numero % 4 == 0)
			printf("El numero %d introducido es divisible por 4 \n", numero);
		else 
			printf("El numero %d introducido es indivisible por 4 \n", numero);
	}
	return(0);
}
