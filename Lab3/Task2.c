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
int fd1, fd2;
if((fd1 = open("foo", O_RDWR)) < 0){
	err_sys("open file error.\n");
}
//create and open new file clone1
//use umask(0) to allow making file with right perms
//rw-rw-rw
umask(0);
if((fd2 = open("clone1", O_RDWR | O_CREAT , 0666)) < 0){
	err_sys("create file error.\n");
}

printf("both files opened successfully.\n");
char b[1];
while((read(fd1, b, 1)) > 0){
	write(fd2, b, 1);
}


//close foo
if(close(fd1) != 0){
	err_sys("error closing read file.");
}
//close clone1
if(close(fd2) != 0){
	err_sys("error closing write file.");
}
umask(0022);
return 0;
}
