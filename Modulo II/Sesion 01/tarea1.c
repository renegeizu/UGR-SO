#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[]){
	int fd;
	if((fd = open("archivo", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	if(write(fd, buf1, 10) != 10){
		perror("\nError en primer write");
		exit(EXIT_FAILURE);
	}
	if(lseek(fd, 40, SEEK_SET) < 0){
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}
	if(write(fd, buf2, 10) != 10){
		perror("\nError en segundo write");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
