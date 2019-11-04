#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

void recorrerDirectorios(DIR *direct, char pathname[], int *reg, int *tamanio){
	struct stat atributos; struct dirent *entrada;
	DIR *directorio; char cadena[1000];
	while((entrada = readdir(direct)) != NULL){
		if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
			sprintf(cadena, "%s/%s", pathname, entrada->d_name);
			if(stat(cadena, &atributos) < 0) {
				perror("\nError en lstat");
				exit(-1);
			}
			if (S_ISDIR(atributos.st_mode)){
				directorio = opendir(cadena);
				if (directorio == NULL)
					printf("\nError al abrir el directorio: %s \n", cadena);
				else
					recorrerDirectorios(directorio, cadena, reg, tamanio);
			}else{
				printf("%s %ld \n", cadena, atributos.st_ino);
				if (S_ISREG(atributos.st_mode)){
					if (((((atributos.st_mode) & ~S_IFMT) & 011) == 011)){
						(*reg)++;
						(*tamanio) += (int) atributos.st_size;
					}
				}
			}
		}
	}
	closedir(direct);
}

int main(int argc, char *argv[]){
	DIR *directorio;
	char pathname[1000];
	int reg = 0, tamanho = 0;
	if (argc == 2){
		strcpy(pathname, argv[1]);
	}else{
		strcpy(pathname, ".");
	}
	if((directorio = opendir(pathname)) == NULL){
		printf("Error al abrir el directorio \n");
		exit(-1);
	}
	printf("Los inodos son: \n");
	recorrerDirectorios(directorio, pathname, &reg, &tamanho);
	printf("Hay %d archivos regulares con permiso x para grupo y otros \n", reg);
	printf("El tamaño total ocupado por dichos archivos es %d bytes \n", tamanho);
	return 0;
}