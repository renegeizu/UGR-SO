#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int i;
	struct stat atributos;
	char tipoArchivo[30];
	if(argc < 2){
		printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}
	for(i = 1; i < argc; i++){
		printf("%s: ", argv[i]);
		if(lstat(argv[i], &atributos) < 0){
			printf("\nError al intentar acceder a los atributos de %s", argv[i]);
			perror("\nError en lstat");
		}else{
			if(S_ISREG(atributos.st_mode)) 
				strcpy(tipoArchivo, "Regular");
			else if(S_ISDIR(atributos.st_mode))
				strcpy(tipoArchivo, "Directorio");
			else if(S_ISCHR(atributos.st_mode))
				strcpy(tipoArchivo, "Especial de caracteres");
			else if(S_ISBLK(atributos.st_mode))
				strcpy(tipoArchivo, "Especial de bloques");
			else if(S_ISFIFO(atributos.st_mode))
				strcpy(tipoArchivo, "Tuberia con nombre (FIFO)");
			else if(S_ISLNK(atributos.st_mode))
				strcpy(tipoArchivo, "Enlace relativo (soft)");
			else if(S_ISSOCK(atributos.st_mode))
				strcpy(tipoArchivo, "Socket");
			else 
				strcpy(tipoArchivo, "Tipo de archivo desconocido");
			printf("%s\n",tipoArchivo);
		}
	}
	return EXIT_SUCCESS;
}
