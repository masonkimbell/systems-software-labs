//Mason Kimbell
//ctrlc2.c
//04/08/2020

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
	printf("OUCH - I got signal %d\n", sig);
}

int main(){
	struct sigaction act;
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESETHAND;
	
	sigaction(SIGINT, &act, 0);
	
	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}

//to run this process in the background, use ./ctrlc2 &
//then to kill the process, use kill -9 <pid>
