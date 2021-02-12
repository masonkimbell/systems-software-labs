#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv){
	if(argc != 3){
		printf("error: not enough/too many parameters\n");
		printf("must enter two parameters: input and output file names\n");
		return 1;
	}
	umask(0);
	int fd1, fd2;
	if((fd1 = open(argv[1], O_RDONLY)) < 0){
		printf("open file error\n");
		return 1;
	}
	if((fd2 = open(argv[2], O_RDWR | O_CREAT, 0600)) < 0){
		printf("create file error\n");
		return 1;
	}

	char b[1];
	char intb[1];
	
	dup2(fd2, 1); //change stdout to fd2

	while((read(fd1, b, 1)) > 0){
		intb[0] = (int)b[0];
		printf("%d ", intb[0]);
	}

	close(fd1);
	close(fd2);

	return 0;
}
