//Mason Kimbell
//Task3.c
//04/08/2020

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	int fd;
	umask(0);
	fd = open("foo", O_RDWR | O_CREAT, 0666);
	
	pid_t pid;
	pid = fork();
	if(pid == 0){
		char buf[] = "Hi, Mom";
		int len = sizeof(buf);
		write(fd, &buf, len);
		_exit(0);
	}
	
	int status;
	pid = wait(&status);
	
	int size = lseek(fd, 0, SEEK_END);
	char *b;
	b = (char*) malloc(size+1);
	lseek(fd, 0, SEEK_SET);
	read(fd, b, size);
	b[size] = '\0';
	printf("My son said %s\n", b);
	exit(0);
}
