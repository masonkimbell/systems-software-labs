#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void increase(int semid, int semno){
	struct sembuf sb;
	sb.sem_num = semno;

	sb.sem_op = 1;
	semop(semid, &sb, 1);
}

void decrease(int semid, int semno){
	struct sembuf sb;
	sb.sem_num = semno;

	sb.sem_op = -1;
	semop(semid, &sb, 1);
}

int main(){
	key_t key;
	int semid;
	union semun arg;

	if((key = ftok("sinit.c", 'J')) == -1){
		puts("ftok error");
		exit(1);
	}

	pid_t pid;
	pid = fork();

	if(pid == 0){
		while(1){
			decrease(semid, 0);
			decrease(semid, 1);
			puts("child is in critical section");
			increase(semid, 0);
			increase(semid, 1);
		}
	}else{
		while(1){
			decrease(semid, 0);
			decrease(semid, 1);
			puts("parent is in critical section");
			increase(semid, 0);
			increase(semid, 1);
		}
	}

	return 0;
}
