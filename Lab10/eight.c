#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(){
	pid_t pid;
	int pipearr[2];
	int secondpipe[2];
	pipe(pipearr);
	pipe(secondpipe);

	pid = fork();

	if(pid == 0){
		close(pipearr[1]);
		close(secondpipe[0]);
		int val1, val2;
		char b[BUFSIZ];
		while(read(pipearr[0], b, BUFSIZ) > 0){
			if((sscanf(b, "%d %d", &val1, &val2)) == 2){
				int product = val1 * val2;
				char b2[BUFSIZ];
				sprintf(b2, "%d", product);
				write(secondpipe[1], b2, strlen(b2));
			}else{
				puts("invalid input");
			}
		}
	}else{
		close(pipearr[0]);
		close(secondpipe[1]);
		int n;
		char b[BUFSIZ];
		puts("enter two integers");
		while((n = read(1, b, BUFSIZ)) > 0){
			write(pipearr[1], b, n);
			char b2[BUFSIZ];
			int max;
			max = read(secondpipe[0], b2, BUFSIZ);
			write(1, b2, max);
		}
	}
}
