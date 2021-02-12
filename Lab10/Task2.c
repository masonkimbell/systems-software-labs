#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define N 10
int ccount = 1;
int pcount = 1;
int count = 0;

void *producer(){
	while(1){
		if(count == N){
			puts("producer is sleeping");
			pcount = 0;
			while(pcount == 0)
				;
		}
		count++;
		printf("count = %d\n", count);
		if(count == 1){
			ccount = 0;
			puts("consumer woke up");
		}
	}
}

void *consumer(){
	while(1){
		if(count == 0){
			puts("consumer is sleeping");
			ccount = 0;
			while(ccount == 0)
				;
		}
		count--;
		printf("count = %d\n", count);
		if(count == N-1){
			puts("producer woke up");
			pcount = 1;
		}
	}
}

int main(){
	pthread_t threads[2];
	int rc;
	if((rc = pthread_create(&threads[0], NULL, producer, NULL)) != 0)
		puts("error");
	if((rc = pthread_create(&threads[1], NULL, consumer, NULL)) != 0)
		puts("error");
	void *tmp1, *tmp2;
	pthread_join(threads[0], &tmp1);
	pthread_join(threads[1], &tmp2);
	return 0;
}
