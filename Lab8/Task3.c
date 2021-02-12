//Mason Kimbell
//Task3.c
//04/14/2020

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 256

int main(){
	int fd[2];
	pid_t pid;
	
	//create a pipe
	if(pipe(fd) < 0){
		puts("pipe error");
		exit(1);
	}
	
	//create a child process
	if((pid = fork()) < 0){
		puts("fork error");
		exit(1);
	}
	
	char pbuf[MAXLINE];
	char cbuf[MAXLINE];

	int n;
	int n2;
	int val1;
	int val2;
	
	
	if(pid > 0){ //parent process
		close(fd[0]); //parent writes, so close read end of pipe
		int first = 0;
		puts("enter two integers");
		while((n = read(STDIN_FILENO, pbuf, MAXLINE)) > 0){
			write(fd[1], pbuf, n);
			sleep(1);
			puts("enter two integers");
		}
	}else{ //child process	
		close(fd[1]); //child reads, so close write end of pipe
		while((n2 = read(fd[0], cbuf, MAXLINE)) > 0){
			if(sscanf(cbuf, "%d%d", &val1, &val2) == 2){
				sprintf(cbuf, "%d\n", val1 + val2);
				n2 = strlen(cbuf);
				if(write(STDOUT_FILENO, cbuf, n2) != n2){
					printf("write error");
					exit(1);
				}
			}else{
				if(write(STDOUT_FILENO, "invalid args\n", 13) != 13){
					printf("write error");
					exit(1);
				}
			}
		}
	}
	return 0;
}
