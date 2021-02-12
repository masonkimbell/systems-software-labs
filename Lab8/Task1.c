//Mason Kimbell
//Task1.c
//04/14/2020

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 2

void *factorial(void *val){
	int n;
	n = (int)val;
	int start = n;
	int mult = n-1;
	while(mult > 0){
		n *= mult;
		mult--;
	}
	printf("%d factorial is %d\n", start, n);
}

void *sumup(void* val){
	int n;
	n = (int)val;
	int start = n;
	int sum = n-1;
	while(sum > 0){
		n += sum;
		sum--;
	}
	printf("1+2+...+%d is %d\n", start, n);
}

int main(int argc, char **argv){
	if(argc < 2){
		puts("error: no arg passed");
		exit(1);
	}
	int n = atoi(argv[1]);
	int rc, rc2;
	pthread_t threads[NUM_THREADS];
	rc = pthread_create(&threads[0], NULL, factorial, (void *)n);
	if(rc){
		puts("return code error in thread 1");
		exit(1);
	}
	rc2 = pthread_create(&threads[1], NULL, sumup, (void *)n);
	if(rc2){
		puts("return code error in thread 2");
		exit(1);
	}
	pthread_exit(NULL);

	return 0;
}
