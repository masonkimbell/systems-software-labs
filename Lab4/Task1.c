//Mason Kimbell
//Task1.c
//find integer embedded in string, convert to int, add 10, and convert back to string
//03/11/2020

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int convertIntToStr(char *str, int x){
	sprintf(str, "%d", x);
	return (strlen(str));
}

int st_to_int(char *str){
	int num = 0;
	int i = 0;
	while(str[i] != '\0'){
		num = 10 * num + (str[i] - '0');
		i++;
	}
	return num;
}

int main(int argc, char **argv){
	if(argc < 2){
		printf("error: no params");
		return 1;
	}
	
	int fd1;
	if((fd1 = open(argv[1], O_RDONLY)) < 0){
		printf("error opening file");
		return 1;
	}

	int i = 0;
	char b[80];
	//keep reading into the same position of b until character is an integer
	while(read(fd1, &b[i], 1) > 0){
		if((int)b[i] >= (int)'0' && (int)b[i] <= (int)'9'){
			i++;
		}
	}
	//null terminate end of string
	b[i] = '\0';
	
	int len = i;
	int val = 0;
	for(i = 0; i < len; i++){
		val = 10 * val + (b[i] - '0');
	}
	val += 10;

	len = convertIntToStr(b, val);
	
	//write number to output with system call
	write(1, b, len);
	printf("\n");
	close(fd1);
	return 0;
}
