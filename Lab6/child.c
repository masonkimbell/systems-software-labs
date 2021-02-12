//Mason Kimbell
//child.c
//used by forkExec.c
//4/1/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv){
	int n = atoi(argv[2]);
	int t = atoi(argv[3]);
	pid_t pid;
	for(; n > 0; n--){
		printf("%s, pid = %d\n", argv[1], pid);
		sleep(t);
	}
	return 37;
}
