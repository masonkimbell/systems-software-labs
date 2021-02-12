#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#define MUTEX 0
#define FULL 1
#define EMPTY 2
#define N 10

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

void down(int semid, short semnum){
	struct sembuf sb;
	sb.sem_num = semnum;
	sb.sem_op = -1;
	semop(semid, &sb, 1);
}

void up(int semid, short semnum){
	struct sembuf sb;
	sb.sem_num = semnum;
	sb.sem_op = 1;
	semop(semid, &sb, 1);
}

void *producer(void *semid){
	int full_bef;
	int full_aft;
	int mutex_bef;
	int mutex_aft;
	int empty_bef;
	int empty_aft;
	int sid;
	sid = (int) semid;
	while(1){
		empty_bef = semctl(sid, EMPTY, GETVAL);
		down(sid, EMPTY);
		empty_aft = semctl(sid, EMPTY, GETVAL);
		printf("empty went from %d to %d\n", empty_bef, empty_aft);

		down(sid, MUTEX);
		mutex_bef = semctl(sid, MUTEX, GETVAL);
		if(mutex_bef == 0)
			puts("mutex locked by producer");

		puts("item inserted");

		up(sid, MUTEX);
		mutex_aft = semctl(sid, MUTEX, GETVAL);
		if(mutex_aft == 1)
			puts("mutex unlocked by producer");

		full_bef = semctl(sid, FULL, GETVAL);
		up(sid, FULL);
		full_aft = semctl(sid, FULL, GETVAL);
		printf("full went from %d to %d\n", full_bef, full_aft);
	}
}

void *consumer(void *semid){
	int full_bef;
	int full_aft;
	int mutex_bef;
	int mutex_aft;
	int empty_bef;
	int empty_aft;
	int sid;
	sid = (int) semid;
	while(1){
		full_bef = semctl(sid, FULL, GETVAL);
		down(sid, FULL);
		full_aft = semctl(sid, FULL, GETVAL);
		printf("full went from %d to %d\n", full_bef, full_aft);
		
		down(sid, MUTEX);
		mutex_bef = semctl(sid, MUTEX, GETVAL);
		if(mutex_bef == 0)
			puts("mutex locked by consumer");
		
		puts("item removed");
		
		up(sid, MUTEX);
		mutex_aft = semctl(sid, MUTEX, GETVAL);
		if(mutex_aft == 1)
			puts("mutex unlocked by consumer");

		empty_bef = semctl(sid, EMPTY, GETVAL);
		up(sid, EMPTY);
		empty_aft = semctl(sid, EMPTY, GETVAL);
		printf("empty went from %d to %d\n", empty_bef, empty_aft);
	}
}

int main(){
	key_t key;
	int semid;
	union semun arg;

	if((key = ftok("Task3.c", 'J')) == -1){
		puts("ftok error");
		exit(1);
	}

	if((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1){
		puts("semget error");
		exit(1);
	}
	arg.val = 1;
	if(semctl(semid, MUTEX, SETVAL, arg) == -1){
		puts("semctl error: MUTEX");
		exit(1);
	}

	arg.val = 0;
	if(semctl(semid, FULL, SETVAL, arg) == -1){
		puts("semctl error: FULL");
		exit(1);
	}

	arg.val = N;
	if(semctl(semid, EMPTY, SETVAL, arg) == -1){
		puts("semctl error: EMPTY");
		exit(1);
	}

	pthread_t threads[2];

	int rc;
	rc = pthread_create(&threads[0], NULL, producer, (void *)semid);
	rc = pthread_create(&threads[1], NULL, consumer, (void *)semid);
	void *tmp1, *tmp2;

	pthread_join(threads[0], &tmp1);
	pthread_join(threads[1], &tmp2);

	return 0;
}
