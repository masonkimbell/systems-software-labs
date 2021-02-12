//Mason Kimbell
//Task3.c
//creates directory structure as seen in lab with symbolic links
//note: home directory is hard-coded
//03/11/2020

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	umask(0);
	if(mkdir("/home/mason/Dir1", 0755) < 0){
		printf("error making directory Dir1");
		return 1;
	}
	if(mkdir("/home/mason/Dir2", 0755) < 0){
		printf("error making directory Dir2");
		return 1;
	}
	if(mkdir("/home/mason/Dir2/Dir21", 0755) < 0){
		printf("error making directory Dir21");
		return 1;
	}
	if(link("/home/mason/code/school/cosc350/labs/Lab-4/hello", "/home/mason/Dir2/Dir21/hello") < 0){
		printf("link error");
		return 1;
	}
	if(symlink("/home/mason/Dir2/Dir21", "/home/mason/Dir1/toDir21") < 0){
		printf("symbolic link error");
		return 1;
	}
	if(symlink("/home/mason/Dir2/Dir21/hello", "/home/mason/Dir1/toHello") < 0){
		printf("symbolic link error");
		return 1;
	}
	return 0;
}
