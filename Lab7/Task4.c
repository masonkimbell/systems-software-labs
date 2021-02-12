//Mason Kimbell
//Task4.c
//04/08/2020

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

static int usr1 = 0;
static int usr2 = 0;

void hdl(int signo){
	if(signo == SIGUSR1){
		usr1 = 1;
	}else if(signo == SIGUSR2){
		usr2 = 1;
	}else{
		puts("did not catch either signal");
	}
}

int main(){
	pid_t pid1;
	pid1 = fork();
	if(pid1 == 0){ //child 1
		kill(getppid(), SIGUSR1);
		exit(0);
	}
	//parent
	(void) signal(SIGUSR1, hdl);
	pause();
	if(usr1)
		puts("Hi Honey! Anything wrong?");
	pid_t pid2;
	pid2 = fork();
	if(pid2 == 0){ //child 2
		kill(getppid(), SIGUSR2);
		exit(0);
	}
	(void) signal(SIGUSR2, hdl);
	pause();
	if(usr2)
		puts("Do you make trouble again?");
	exit(0);
}
