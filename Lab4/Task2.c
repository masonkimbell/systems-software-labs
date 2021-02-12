//Mason Kimbell
//Task2.c
//decode ascii code to original input file
//03/11/2020

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc < 3){
		printf("error: not enough params");
		return 1;
	}
	
	int fd1, fd2;
	if((fd1 = open(argv[1], O_RDONLY)) < 0){
		printf("error opening file");
		return 1;
	}

	if((fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0){
		printf("error creating file");
		return 1;
	}
	
	int i = 0;
	char b[3];
	
	while(read(fd1, &b[i], 1)){
		if(b[i] != ' '){
			i++;
		}else{
			b[i] = '\0';
			//printf("testing %s...\n", b);
			int len = i;
			i = 0;
			int j;
			int num = 0;
			for(j = 0; j < len; j++){
				num = 10 * num + (b[j] - '0');
			}
			//printf("%s = %d\n", b, num);
			char ascii = num;
			write(fd2, &ascii, 1);
			//printf("%d = %c\n", num, ascii);
		}

	}
	close(fd1);
	close(fd2);
	return 0;
}
