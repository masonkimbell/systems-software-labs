#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

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

	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
		puts("msgget error");
		exit(1);
	}
	int ret_val;
	ret_val = mkfifo("HALF_DUPLEX", 0666);
	
	int fd;
	fd = open("HALF_DUPLEX", O_RDONLY);

	char buf2[BUFSIZ];
	int n;

	printf("enter a message\n");
	buf.mtype = 1;
	while(gets(buf.mtext), !feof(stdin)){
		if(msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) < 0){
			puts("msgsnd error");
			exit(1);
		}
		n = read(fd, buf2, BUFSIZ);
		buf2[n] = '\0';
		printf("received message from FIFO: %s\n", buf2);
	}

	if(msgctl(msqid, IPC_RMID, NULL) < 0){
		puts("msgctl error");
		exit(1);
	}

	exit(0);
}
