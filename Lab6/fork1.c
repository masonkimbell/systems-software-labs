//Mason Kimbell
//fork1.c
//4/1/2020

#include <sys/types.h>
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
	
	printf("fork program starting\n");
	pid = fork();
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			n = st_to_int(argv[1]);
			t = st_to_int(argv[3]);
			break;
		default:
			message = "This is the parent";
			n = st_to_int(argv[2]);
			t = st_to_int(argv[4]);
			break;
	}
	
	for(; n > 0; n--){
		puts(message);
		sleep(t);
	}
	exit(0);
}
