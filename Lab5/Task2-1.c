#include <utmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int openUtmpFile(){
	int fd;
	if(chdir("/var/run") < 0){
		printf("error chainging directories\n");
		return -1;
	}
	fd = open("utmp", O_RDONLY);
	if(fd < 0){
		printf("error opening utmp\n");
		return -1;
	}
	return fd;
}

int main(){
	int fd = openUtmpFile();
	if(fd == -1)
		return 1;
	printf("the file descriptor of utmp is %d\n", fd);
	
	if(close(fd) < 0){
		printf("error closing file\n");
		return 1;
	}
	return 0;
}
