#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 50

void *PrintHello(void *threadid);

int main(){
	int i;
	pthread_t  threads[NUM_THREADS] ;
	int *threadid[NUM_THREADS];
	
	for(i=0; i<NUM_THREADS;i++){
		threadid[i] = (int *) malloc(sizeof(int));
		*threadid[i] = i;
		PrintHello(threadid[i]);
	}
	
	pthread_exit(NULL);
	return 0;
}

void *PrintHello(void *threadid){
	
	int thid = *(int*)threadid;
	printf("Hello from thread %d \n", (int)thid + 1);
	fflush(NULL);
	void pthread_exit(void *);
}