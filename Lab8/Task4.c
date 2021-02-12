//Mason Kimbell
//Task4.c
//04/14/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 256

void combineStrings(char* first, char* second, char* buf, int size1, int size2){
	int i;
	for(i = 0; i < size1; i++){
		buf[i] = first[i];
	}
	buf[size1] = ' ';
	for(i = 0; i < size2; i++){
		buf[i + size1 + 1] = second[i];
	}
	buf[size1+size2+1] = '\0';
}

int main(int argc, char** argv){

	char *cmd;
	cmd = argv[1];
	char *fname;
	fname = argv[2];
	int cmd_len, fname_len;
	FILE *ptr;

	cmd_len = strlen(cmd);
	
	fname_len = strlen(fname);
	
	char path[cmd_len+fname_len + 1];
	combineStrings(cmd, fname, path, cmd_len, fname_len);

	printf("%s\n", path);
	
	char buf[BUFSIZ];

	if((ptr = popen(path, "r")) != NULL){
		while(fgets(buf, BUFSIZ, ptr) != NULL)
			printf("%s", buf);
	}
	pclose(ptr);

	return 0;
}
