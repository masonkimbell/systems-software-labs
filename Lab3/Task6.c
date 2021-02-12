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
//set umask to 0 so we can set the correct file perms
umask(0);
//open file foo
int fd1;
if((fd1 = open("foo", O_RDWR)) < 0){
	err_sys("open file error.");
}

//create and open new file foorev w/ rwxrw----
int fd2;
if((fd2 = open("foorev2", O_RDWR | O_CREAT , 0760)) < 0){
	err_sys("create file error.");
}

char b[1];
char nullT[] = "\n";

//calculate size of foo
int nread;
int size = 0;
while((nread = read(fd1, b, 1)) > 0){
	size++;
}

printf("size is %d\n", size);

int i;

//read from foo backwards, write forwards to foorev
//the 2 removes the newline, is added later to the end
//note: might want to change this depending on if I actually need it or not
for(i = 2; i <= size; i++){

	/***Task5 stuff
	if((offset = lseek(fd1, numBytes - i, SEEK_SET)) == -1){
		err_sys("lseek error.");
	}
	//for testing
	//printf("offset is %d\n", offset);
	if(read(fd1, b, 1) < 0){
		err_sys("read error.");
	}
	***/
	
	if((pread(fd1, b, 1, size-i)) == -1){
		err_sys("read error.");
	}

	printf("offset is %d\n", size-i);
	
	if(write(fd2, b, 1) != 1){
		err_sys("write error.");
	}
}

//add newline character to the end
if(write(fd2, nullT, 1) != 1){
	err_sys("write error.");
}

//close foo
if(close(fd1) != 0){
	err_sys("error closing read file.");
}
//close foo1
if(close(fd2) != 0){
	err_sys("error closing write file.");
}

//reset umask back to 0022
umask(0022);
return 0;
}
