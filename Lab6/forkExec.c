//Mason Kimbell
//forkExec.c
//uses child.c
//4/1/2020

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int st_to_int(char* str){
	int i = 0;
	int val = 0;
	while(str[i] != '\0'){
		val = 10 * val + (str[i] - '0');
		i++;
	}
	return val;
}

int main(int argc, char** argv){
	pid_t pid;
	char *message;
	int n,t;
	int exit_code;
	
	printf("fork program starting\n");
	pid = fork();
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			char* arguments[] = {"./child", message, argv[1], argv[3], NULL};
			if(execv(arguments[0], arguments)<0){
				puts("execv error");
				exit(1);
			}
			break;
		default:
			message = "This is the parent";
			n = st_to_int(argv[2]);
			t = st_to_int(argv[4]);
			exit_code = 0;
			break;
	}
	
	for(; n > 0; n--){
		printf("%s, pid = %d\n", message, pid);
		sleep(t);
	}

	if(pid != 0){ //is the parent
		int stat_val;
		pid_t child_pid;
		child_pid = wait(&stat_val);
		
		printf("Child has finished: PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child termintated abnormally\n");
	}
	exit(exit_code);
	/*
	forkWait is different from fork1 because the program will wait until the
	child is done running before the terminal prompt appears. In fork1, the
	terminal prompt would appear after the parent finishes running regardless
	of whether or not the child is still running.
	*/
}
