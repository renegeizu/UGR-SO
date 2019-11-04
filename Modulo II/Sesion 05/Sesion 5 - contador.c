#include <signal.h>
#include <stdio.h>

static int s_recibidas[65];

static void handler (int i){
	s_recibidas[i]++;
	printf("\n La señal %d , se ha realizado %d veces ", i, s_recibidas[i]);
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	int i;
	for(i = 0; i < 65; i++)
		s_recibidas[i] = 0;
	for(i = 0; i < 65; i++)
		if(sigaction(i, &sa, NULL) < 0)
			printf("\n No puedo capturar la señal %d ", i);
	while(1);
}
