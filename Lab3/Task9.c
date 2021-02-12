#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int palind(int fd1, int fd2){
	int wordSize = 0;
	int offset;
	int offset2;
	int fileSize = 0;
	int curr = 0;
	char b;

	//calculate file size
	while(read(fd1, &b, 1) > 0){
		fileSize++;
	}

	//set fd1 back to beginning
	offset = lseek(fd1, 0, SEEK_SET);
	//run through the whole file

	while(curr < fileSize){
		wordSize = 0;
		//get fd2 to the end of the word
		while(read(fd2, &b, 1) > 0){
			//printf("reading %s", b);
			wordSize++;
			if(b == ' ' || b == '\n'){
				offset2 = lseek(fd2, -1, SEEK_CUR);
				break;
			}
		}
		wordSize--;
		
		//at this point:
		//fd1: beginning of word
		//fd2: end of word
		//wordSize: size of word
		//fileSize: size of whole file

		//todo: test current word
		char word[wordSize];
		int k;
		offset = lseek(fd1, -wordSize, SEEK_CUR);
		for(k = 0; k < wordSize; k++){
			read(fd1, &b, 1);
			word[k] = b;
		}
		offset = lseek(fd1, -wordSize, SEEK_CUR);
		word[wordSize] = '\0';

		//test palindrome function goes here
		//only do this for words bigger than 1 character
		if(wordSize > 1){
			int begin = 0;
			int end = wordSize-1;
			int palind = 1;
			while(begin < end){
				if(word[begin] != word[end]){
					palind = 0;
					break;
				}
				begin++;
				end--;
			}
			if(palind){
				printf("%s is a palindrome .\n" , word);
				return 1;
			}
		}

		offset = lseek(fd1, wordSize+1, SEEK_CUR);
		curr += wordSize + 1;
	}
	return 0;
}

int main(int argc, char **argv){
	if(argc < 2){
		printf("error: did not pass file name\n");
		return 1;
	}
	int fd1, fd2;
	if((fd1 = open(argv[1], O_RDONLY)) < 0){ 
		printf("error opening file");
		return 1;
	}
	fd2 = dup(fd1);

	if(palind(fd1, fd2)){
		printf("%s contains a palindrome\n", argv[1]);
	}else{
		printf("%s does not contain a palindrome\n", argv[1]);
	}
	close(fd1);
	close(fd2);
}
