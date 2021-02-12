//Mason Kimbell
//Task5.c
//4/1/2020

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

//returns 1 if integer, 0 if not
int isInteger(char a){
	if((int) a >= (int) '0' && (int) a <= (int) '9')
		return 1;
	else
		return 0;
}

int main(int argc, char **argv){
	int fd;
	if((fd = open(argv[1], O_RDONLY)) < 0){
		puts("open error");
		exit(1);
	}
	int size = lseek(fd, 0, SEEK_END);
	char b;
	char c;
	int o1 = 0;
	int o2 = 0;
	int childFile, parentFile;
	umask(0);
	if((childFile = open("child.txt", O_WRONLY | O_CREAT, 0666)) < 0){
		puts("create error");
		exit(1);
	}
	if((parentFile = open("parent.txt", O_WRONLY | O_CREAT, 0666)) < 0){
		puts("create error");
		exit(1);
	}
	pid_t pid;
	if((pid = fork()) < 0){
		puts("fork error");
		exit(1);
	}
	int i, j;
		if(pid == 0){ //child
			for(i = 0; i < size; i++){
				lseek(fd, o1, SEEK_SET);
				read(fd, &c, 1);
				if(!isInteger(c))
					write(childFile, &c, 1);
				o1++;
			}
			_exit(0);
		}else{
			int k;
			for(k = 0; k < size * size; k++)
				continue;
			for(j = 0; j < size; j++){
				lseek(fd, o2, SEEK_SET);
				read(fd, &b, 1);
				if(isInteger(b))
					write(parentFile, &b, 1);
				o2++;
			}
		}
	close(childFile);
	close(parentFile);
	close(fd);
	exit(0);
}
