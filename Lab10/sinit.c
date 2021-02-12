#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(){
	key_t key;
	int semid;
	union semun arg;

	if((key = ftok("sinit.c", 'J')) == -1){
		puts("ftok error");
		exit(1);
	}

	if((semid = semget(key, 2, 0666 | IPC_CREAT)) == -1){
		puts("semget error");
		exit(1);
	}
	arg.val = 1;
	if(semctl(semid, 0, SETVAL, arg) == -1){
		puts("semctl error: MUTEX");
		exit(1);
	}

	if(semctl(semid, 1, SETVAL, arg) == -1){
		puts("semctl error: FULL");
		exit(1);
	}

	return 0;
}
