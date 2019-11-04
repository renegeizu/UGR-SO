#include <signal.h>
#include <stdio.h>

int main(){
	sigset_t mascara;
	sigemptyset(&mascara);
	sigfillset(&mascara);
	sigdelset(&mascara, SIGUSR1);
	sigsuspend(&mascara);
}
