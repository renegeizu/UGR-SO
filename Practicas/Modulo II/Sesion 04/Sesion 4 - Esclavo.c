//gcc Esclavo.c -lm -o Esclavo

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int inicio = atoi(argv[1]), final = atoi(argv[2]), i, j, primo;
	for (i = inicio; i < final; i++){
		primo = 1;
		for(j = 2; j <= ((int) sqrt(i)) && primo; j++){
			if(i % j == 0){
				primo = 0;
			}
		}
		if(primo)
			write(STDOUT_FILENO, &i, sizeof(int));
	}
	return 0;
}
