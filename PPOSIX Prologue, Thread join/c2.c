#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8

char *messages[NUM_THREADS];

void *PrintHello(void *threadid){
	
	int thid = *((int*)threadid);
	printf("Thread %d: %s\n", thid + 1, messages[thid]);
	pthread_exit(NULL);
}

int main(){
	pthread_t  threads[NUM_THREADS] ;
	int i,result;
	int *taskids[NUM_THREADS];

	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";
	
	for(i=0; i<NUM_THREADS;i++){

		taskids[i] = (int *)malloc(sizeof(int));
		*taskids[i] = i;
		
		result = pthread_create(&threads[i], NULL, PrintHello, (void*) taskids[i]);
		if(result != 0) printf("Error %d creating thread...\n", result);
	}
	
	pthread_exit(NULL);
	return 0;
}
