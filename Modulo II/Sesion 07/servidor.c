#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int estado;

static void mimanejador(int signal){
	pid_t pid = wait(&estado);
}

int main(int argc, char *argv[]){
	int fd_e, fd_s, fd_bloqueo, temporal;
	char fifo_e[50], fifo_s[50], fifo_proxy[50];
	int leidos, proxy_pid;
	pid_t pid;
	if(argc != 2){
		printf("Uso: Servidor <nombre_fifo>");
		exit(-1);
	}
	signal(SIGCHLD, mimanejador);
	sprintf(fifo_s, "%ss", argv[1]);
	sprintf(fifo_e, "%se", argv[1]);
	umask(0);
	mkfifo(fifo_e, 0666);
	mkfifo(fifo_s, 0666);
	if((fd_s = open(fifo_s, O_RDWR)) < 0){
		perror("Servidor: Error open del fifo servidor");
		exit(-1);
	}
	if((fd_e = open(fifo_e, O_RDWR)) < 0){
		perror("Servidor: Error open del fifo cliente");
		exit(-1);
	}
	umask(0);
	if((fd_bloqueo = open("bloqueo", O_CREAT, 0666)) < 0){
		printf("Servidor: Error open archivo bloqueo");
		exit(-1);
	}
	while((leidos = read(fd_e, &temporal, sizeof(int))) != 0){
		pid = fork();
		if(pid == 0){
			proxy_pid = getpid();
			sprintf(fifo_proxy, "fifo.%d", proxy_pid);
			umask(0);
			mkfifo(fifo_proxy, 0666);
			write(fd_s, &proxy_pid, sizeof(int));
			dup2(open(fifo_proxy, O_RDONLY), STDIN_FILENO);
			execlp("./proxy", "proxy", NULL);
			exit(0);
		}
	}
	return 0;
}
