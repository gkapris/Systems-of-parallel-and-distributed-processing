#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5
char *messages[NUM_THREADS];

struct thread_data{
	int thread_id;
	int sum;
	char *message;	
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadid){
	
	struct thread_data *mydata;
	
	mydata = (struct thread_data*) threadid;
	
	int taskid = mydata -> thread_id;
	int tasksum = mydata -> sum;
	char *msg = mydata -> message;
	
	printf ("Thread %d: %s, sum = %d\n", taskid + 1, msg, tasksum);

	pthread_exit(NULL);
}

int main(){
	int i,result,summ;
	int *taskids[NUM_THREADS];
	pthread_t  threads[NUM_THREADS] ;
	
	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";
	
	for(i=0; i<NUM_THREADS;i++){
		
		thread_data_array[i].thread_id = i;
		thread_data_array[i].sum = summ;
		thread_data_array[i].message = messages[i];
		
		summ = summ + i + 1;
		
		taskids[i] = (int *)malloc(sizeof(int));
		*taskids[i] = i;
		
		result = pthread_create(&threads[i], NULL, PrintHello, (void*) &thread_data_array[i]);
		if(result != 0) printf("Error %d creating thread...\n", result);
	}
	
	pthread_exit(NULL);
	return 0;
}