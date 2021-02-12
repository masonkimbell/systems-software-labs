//Mason Kimbell
//ctrlc1.c
//04/08/2020

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
}

int main(){
	(void) signal(SIGINT, ouch);
	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}
