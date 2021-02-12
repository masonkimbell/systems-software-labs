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
	err_sys("open file error.\n");
}
//create and open new file clone2
int fd2;
//set umask(0)
//rwxrwx---
umask(0);
if((fd2 = open("clone2", O_RDWR | O_CREAT , 0770)) < 0){
	err_sys("create file error.\n");
}

printf("both files opened successfully.\n");
char b[32];
int nread;
while((nread = read(fd1, b, 32)) > 0){
	if(nread != 32){
		int i;
		for(i = 0; i < 32; i++){
			if(nread < i+1)
				b[i] = ' ';
		}
	}
	write(fd2, b, 32);
}


//close foo
if(close(fd1) != 0){
	err_sys("error closing read file.");
}
//close clone2
if(close(fd2) != 0){
	err_sys("error closing write file.");
}
printf("copied contents of foo into clone2\n");
return 0;
}
