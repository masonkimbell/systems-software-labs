//Mason Kimbell
//Task2.c
//04/14/2020

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int *arr;
int arr_size = 0;

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

void sort_arr(){
	int i, j, min;
	
	for(i = 0; i < arr_size - 1; i++){
		min = i;
		for(j = i+1; j < arr_size; j++){
			if(arr[j] < arr[min])
				min = j;
		}
		swap(&arr[min], &arr[i]);
	}
}

void *getScores(){
	int n = 1;
	while(n > 0 && arr_size <= 20){
		printf("enter a number to add to the score list or -1 to exit\n");
		scanf("%d", &n);
		if(n > 0){
			arr_size++;
			arr = (int *)realloc(arr, arr_size * sizeof(int));
			arr[arr_size-1] = n;
		}
	}
	return ((void *) 1);
}

void *avg(){
	int i;
	int sum = 0;

	for(i = 0; i < arr_size; i++){
		sum += arr[i];
	}

	printf("the avg score is %f\n", sum/(float)arr_size);

	sort_arr();

	printf("the middle score is %d\n", arr[arr_size/2]);
	return ((void *) 2);
}

void *minmax(){
	int i;
	int min = arr[0];
	int max = arr[0];
	pthread_mutex_lock(&mutex);
	for(i = 0; i < arr_size; i++){
		if(arr[i] < min)
			min = arr[i];
	}
	for(i = 0; i < arr_size; i++){
		if(arr[i] > max)
			max = arr[i];
	}
	pthread_mutex_unlock(&mutex);
	printf("the min score is %d\n", min);
	printf("the max score is %d\n", max);
	return ((void *) 3);
}

void *clear(){
	int i;
	for(i = 0; i < arr_size; i++){
		arr[i] = 0;
	}
	puts("array is cleared:");
	for(i = 0; i < arr_size; i++){
		printf("%d ", arr[i]);
	}
	puts("");
	return ((void *) 4);
}

int main(int argc, char **argv){

	int rc;
	void *tret1, *tret2, *tret3, *tret4;

	pthread_t threads[NUM_THREADS];
	if((rc = pthread_create(&threads[0], NULL, getScores, NULL)) != 0){
		puts("thread create error");
		exit(1);
	}

	if((rc = pthread_join(threads[0], &tret1)) != 0){
		puts("thread join error");
		exit(1);
	}
		
	if((rc = pthread_create(&threads[1], NULL, avg, NULL)) != 0){
		puts("thread create error");
		exit(1);
	}
	

	if((rc = pthread_create(&threads[2], NULL, minmax, NULL)) != 0){
		puts("thread create error");
		exit(1);
	}

	if((rc = pthread_join(threads[1], &tret2)) != 0){
		puts("thread join error");
		exit(1);
	}

	if((rc = pthread_join(threads[2], &tret3)) != 0){
		puts("thread join error");
		exit(1);
	}
	
	if((rc = pthread_create(&threads[3], NULL, clear, NULL)) != 0){
		puts("thread create error");
		exit(1);
	}

	if((rc = pthread_join(threads[3], &tret4)) != 0){
		puts("thread join error");
		exit(1);
	}

	puts("all threads exited");
	free(arr);
	pthread_exit(NULL);
	
	return 0;
}
