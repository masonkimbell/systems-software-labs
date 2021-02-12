#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

struct my_msgbuf{
	long mtype;
	char mtext[20];
};

int main(){
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if((key = ftok("msgQsnd.c", 'B')) < 0){
		puts("ftok error");
		exit(1);
	}

	if((msqid = msgget(key, 0666)) < 0){
		puts("msgget error");
		exit(1);
	}

	puts("receiving...");
	int fd;
	fd = open("HALF_DUPLEX", O_WRONLY);
	while(1){
		if(msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 0, 0) < 0){
			exit(0);
		}
		
			printf("received message from msgqueue: %s\n", buf.mtext);
			write(fd, "I got it", 8);
	}
	exit(0);
}
