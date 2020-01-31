#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
	DIR *directorio; long permisos; char *pathname;
	struct stat atributos; struct dirent *entrada;
	char archivo[100], archivo2[100];
	if (argc != 3){
		printf("<nombre_de_archivo> <permisos_nuevos> \n");
		exit(-1);
	}
	pathname = argv[1]; directorio = opendir(pathname);
	permisos = strtol(argv[2], NULL, 8); readdir(directorio);
	while((entrada = readdir(directorio)) != NULL){
		sprintf(archivo, "%s/%s", pathname, entrada->d_name);
		if(lstat(archivo, &atributos) < 0) {
			perror("Error en stat \n"); exit(-1);
		}else if(S_ISREG(atributos.st_mode)){
			sprintf(archivo2, "%s", entrada->d_name);
			printf("%s: %o ", archivo2, atributos.st_mode);
			if(chmod(archivo, permisos) < 0){
				printf("Error en chmod \n"); exit(-1);
			}else{
				stat(archivo, &atributos);
				printf("%o \n", atributos.st_mode);
			}
		}
	}
	closedir(directorio);
	return 0;
}