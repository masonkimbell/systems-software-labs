//Mason Kimbell
//Task5.c
//04/08/2020

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(){
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	
	if(sigprocmask(SIG_BLOCK, &mask, NULL) < 0){
		perror("sigprocmask");
		return 1;
	}

	int i;
	for(i = 1; i <= 5; i++){
		printf("%d\n", i);
		sleep(1);
	}

	sigset_t unblock;
	sigemptyset(&unblock);
	sigaddset(&unblock, SIGQUIT);
	sigsuspend(&unblock);
	if(sigprocmask(SIG_UNBLOCK, &unblock, NULL) < 0){
		perror("sigprocmask");
		return 1;
	}
	sigsuspend(&unblock);	
	for(i = 1; i <= 5; i++){
		sigsuspend(&unblock);
		printf("%d\n", i);
		sleep(1);
	}
	return 0;
}
