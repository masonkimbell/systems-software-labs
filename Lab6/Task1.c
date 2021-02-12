//Mason Kimbell
//Task1.c
//4/1/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

char* mygetenv(const char* name){
	char **p = environ;
	while(*p != NULL){
		int index = 0;
		int length = strlen(name);
		char* substring;
		substring = malloc((length+1)*sizeof(char));
		int i;
		for(i = 0; i < length; i++){
			substring[i] = p[index][i];
		}
		substring[length] = '\0';
		//printf("name = %s, substring = %s\n", name, substring);
		if(strcmp(name, substring) == 0){
			//printf("found the substring\n");
			//printf("name = %s, substring = %s\n", name, substring);
			int j = length + 1;
			int size = 0;
			while(p[index][j] != '\0'){
				size++;
				j++;
			}
			j = length + 1;
			int k = 0;
			char* ret;
			ret = malloc(size*sizeof(char));
			while(p[index][j] != '\0'){
				ret[k] = p[index][j];
				k++;
				j++;
			}
			ret[size] = '\0';
			return ret;
		}
		free(substring);
		*p++;
		index++;
	}
}

int main(int argc, char **argv, char **envp){
	printf("~~~getenv~~~\n");
	printf("PATH: %s\n", getenv("PATH"));
	printf("HOME: %s\n", getenv("HOME"));
	printf("ROOT: %s\n", getenv("ROOT"));
	printf("PWD: %s\n", getenv("PWD"));
	printf("LOGNAME: %s\n", getenv("LOGNAME"));
	printf("~~~mygetenv~~~\n");
	printf("PATH: %s\n", mygetenv("PATH"));
	printf("HOME: %s\n", mygetenv("HOME"));
	printf("ROOT: %s\n", mygetenv("ROOT"));
	printf("PWD: %s\n", mygetenv("PWD"));
	printf("LOGNAME: %s\n", mygetenv("LOGNAME"));
	return 0;
}
