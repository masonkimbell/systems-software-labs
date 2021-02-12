#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void err_sys(char *str){
	printf("%s", str);
	exit(1);
}

int main(){
//open file foo
int fd1;
if((fd1 = open("foo", O_RDWR)) < 0){
	err_sys("open file error.");
}

//open file foo1
int fd2;
if((fd2 = open("foo1", O_RDWR)) < 0){
	err_sys("open file error.");
}

umask(0);
//create and open new file foo12 w/ rwxrw----
int fd3;
if((fd3 = open("foo12", O_RDWR | O_CREAT , 0760)) < 0){
	err_sys("create file error");
}

char b[1];
int offset;

//set offset to the end of fd3
if((offset = lseek(fd3, 1, SEEK_END)) == -1){
	err_sys("lseek error.");
}

//read foo into foo12
while(read(fd1, b, 1) > 0){
	if(write(fd3, b, 1) != 1){
		err_sys("write error.");
	}
}

while(read(fd2, b, 1) > 0){
	if(write(fd3, b, 1) != 1){
		err_sys("write error.");
	}
}

//close foo
if(close(fd1) != 0){
	err_sys("error closing read file 1.");
}
//close foo1
if(close(fd2) != 0){
	err_sys("error closing read file 2.");
}
//close foo2
if(close(fd3) != 0){
	err_sys("error closing write file");
}
//reset umask back to 0022
umask(0022);
return 0;
}
