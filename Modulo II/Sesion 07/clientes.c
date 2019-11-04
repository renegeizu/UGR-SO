#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define tamano 1024
#define longnombre 50

static void mimanejador(int senal){
	printf ("Cliente %d: escribo en el FIFO aun no abierto para lectura\n", getpid());
	return;
}

int obtenerfifo (int dfifoe, int dfifos, int mipid){
	int mififo, resultado, pidproxy;
	char nombrefifoproxy[longnombre];
	if (!(resultado =write (dfifoe,&mipid,sizeof(int)))) {
		perror ("Cliente: error al escribir peticion en fifo conocido del servidor");
		exit(EXIT_FAILURE);
	}
	printf("Cliente %d: escrito pid en fifo conocido del servidor.\n", mipid);
	if (! (resultado = read (dfifos,&pidproxy,sizeof(int)))) {
		perror ("Cliente: error al leer fifo proxy asignado por servidor");
		exit(EXIT_FAILURE);
	}
	printf("Cliente %d: leido pid %d en fifo de servidor. \n",mipid,pidproxy);
	sprintf(nombrefifoproxy, "fifo.%d", pidproxy);
	if ((mififo = open (nombrefifoproxy, O_WRONLY)) == -1) {
		perror("Cliente: problema al abrir fifo proxy asignado");
		exit(EXIT_FAILURE);
	}
	return (mififo);
}


void producir (char c, int mififo, int mipid) {
	char bufer[tamano];
	int contador=0, i=0, resultado;
	int numcar;
	srand ((unsigned int) mipid);
	numcar = 1 + (int) (10000.0*rand()/(RAND_MAX+1.0));
	printf("Cliente %d: Numero caracteres %c a generar es %d\n",mipid,c,numcar);
	if (signal(SIGPIPE, mimanejador)== SIG_ERR)
		perror ("Cliente: Error configurando senal");
	while (contador < numcar){
		bufer[i] = c;
		contador++;
		i++;
		if ((i == tamano) || (contador == numcar)) {
			sleep((mipid+contador)%1);
			if ((resultado = write(mififo, bufer, i)) == -1) 
				perror ("ERROR AL ESCRIBIR EN EL FIFO");
			printf("Cliente %d: He escrito en el fifo %d\n",mipid,resultado);
			i = 0;
		}
	}
}

int main (int argc, char **argv) {  
	char c = 'a';
	int numcli, pid, mipid, i, dfifoe, dfifos, mififo, estado;
	char nombrefifoe[longnombre], nombrefifos[longnombre];
	setbuf(stdout, NULL);
	if (argc < 3) {
		printf ("Clientes: Formato: clientes <nombre_fifo> <numero_clientes>\n");
		exit(EXIT_FAILURE);
	}else if ( ((numcli= atoi (argv[2])) > 10) || (numcli < 1) ){
		printf ("Clientes: <numero_clientes> comprendido entre 1 y 10\n");
		exit(EXIT_FAILURE);
	}
	sprintf(nombrefifoe,"%se",argv[1]);
	sprintf(nombrefifos,"%ss",argv[1]);
	if ((dfifoe = open (nombrefifoe, O_WRONLY)) == -1) {
		perror ("Clientes: Problema con el archivo fifo de entrada al servidor");
		exit(EXIT_FAILURE);
	}
	if ((dfifos = open (nombrefifos, O_RDWR)) == -1) {
		perror ("Clientes: Problema con el archivo fifo de salida del servidor");
		exit(EXIT_FAILURE);
	}
	for (i=1; i<numcli; i++) {
		if ((pid = fork()) == -1) {
			perror ("Clientes: Problema al crear proceso cliente");
			exit(EXIT_FAILURE);
		}
		if (pid == 0 ) {
			mipid = getpid();
			mififo = obtenerfifo(dfifoe, dfifos, mipid);
			producir(c, mififo, mipid);
			exit(EXIT_SUCCESS);
		}else
			c++;
	}
	mipid = getpid ();
	mififo = obtenerfifo(dfifoe, dfifos, mipid);
	producir(c, mififo, mipid);
	while (wait(&estado)!=-1);
	exit(EXIT_SUCCESS);
}
