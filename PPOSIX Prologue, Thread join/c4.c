#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NUM_THREADS 4

void computethread (void *t)
{
	int i,tmp;
	double result = 0.0;
	tmp = t;
	printf ("Thread starting with %d: \n", tmp);
	for(i=0;i<pow(10,7); i++){
		result = result + sin(i) + tan(i);
		printf("Thread %d, finished. Result is %f\n", tmp, result);
	}
	pthread_exit(NULL);
}

int main(){
	
	int tmp,status,i;
	int *taskids[NUM_THREADS];
	pthread_t  threads[NUM_THREADS] ;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for(i=0; i < NUM_THREADS; i++){
		taskids[i] = (int *) malloc(sizeof(int));
		*taskids[i] = i;
		status = pthread_create(&threads[i], &attr, computethread, (void *)taskids[i]);
		if(status != 0) printf("Error %d creating thread...\n", status);		
	}
	pthread_attr_destroy(&attr);
	
	for(i=0; i<NUM_THREADS;i++){
		tmp = pthread_join(threads, &status);
		if(tmp != 0) printf("Error %d creating thread...\n", tmp);
		printf("Main: completed join with thread number %d having status of %d \n",i,(int *)status);
	}

return(0);
}