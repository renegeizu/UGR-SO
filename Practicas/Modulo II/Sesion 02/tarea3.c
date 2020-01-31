#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	struct stat atributos;
	if((fd1 = open("archivo1", O_CREAT|O_TRUNC|O_WRONLY, S_IRGRP|S_IWGRP|S_IXGRP)) < 0){
		printf("\nError %d en open(archivo1,...)", errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	umask(0);
	if((fd2 = open("archivo2", O_CREAT|O_TRUNC|O_WRONLY, S_IRGRP|S_IWGRP|S_IXGRP)) < 0){
		printf("\nError %d en open(archivo2,...)", errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	if(stat("archivo1", &atributos) < 0){
		printf("\nError al intentar acceder a los atributos de archivo1");
		perror("\nError en lstat");
		exit(EXIT_FAILURE);
	}
	if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0){
		perror("\nError en chmod para archivo1");
		exit(EXIT_FAILURE);
	}
	if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0){
		perror("\nError en chmod para archivo2");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
