//Task2.c
//Mason Kimbell
//03/25/2020

//Completes both 5.2.1 and 5.2.2 from the lab assignment
//Opens utmp file and returns the file descriptor
//Then loops through the utmp file and reads the record
//Prints username and the number of logged in users

#include <utmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int openUtmpFile(){
	int fd;
	if(chdir("/var/run") < 0){
		printf("error chainging directories\n");
		return -1;
	}
	fd = open("utmp", O_RDONLY);
	if(fd < 0){
		printf("error opening utmp\n");
		return -1;
	}
	return fd;
}

int main(){
	int fd = openUtmpFile();
	if(fd == -1)
		return 1;
	else
		printf("the file descriptor for utmp is %d\n", fd);
	
	struct utmp *info;

	int usercount = 0;

	char b;
	int size = 0;
	while(read(fd, &b, 1) > 0){
		size++;
	} 

	lseek(fd, 0, SEEK_SET);

	int i = 0;
	while(i < size){
		read(fd, info, sizeof(struct utmp));
		printf("%s \n", info->ut_user);
		if(info->ut_type == USER_PROCESS)
			usercount++;
		i += sizeof(struct utmp);
	}		


	printf("found %d logged in user(s)\n", usercount);
	
	if(close(fd) < 0){
		printf("error closing file\n");
		return 1;
	}
	return 0;
}
