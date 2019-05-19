#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHRDS 4
#define VECLEN 100

typedef struct {
	
	double *a ;
	double *b ;
	double sum;
	int veclen;
	
}DOTDATA;

void *compute_multiplication(void *t);

DOTDATA dotstr;
pthread_t threads[NUMTHRDS];
pthread_mutex_t mutexsum;

int main(int argc, char *argv[]){
	
	int i, t, error;
	pthread_mutexattr_t attr;
	pthread_attr_t attrb;
	int *threadid[NUMTHRDS];
	void *status;
	double *a, *b;
	
	pthread_mutex_init(&mutexsum, &attr);
	pthread_attr_init(&attrb);
	pthread_attr_setdetachstate(&attrb, PTHREAD_CREATE_JOINABLE);
	a = (double *) malloc (NUMTHRDS*VECLEN*sizeof(double));
	b = (double *) malloc (NUMTHRDS*VECLEN*sizeof(double));
	
	for (i=0; i<VECLEN*NUMTHRDS; i++){
		a[i] = 1.0;
		b[i] = 2*a[i];
	}
	
	dotstr.veclen = VECLEN;
	dotstr.a = a;
	dotstr.b = b;
	dotstr.sum = 0;
	for (t=0; t<NUMTHRDS; t++) {
		
		threadid[t] = (int *) malloc (sizeof(int));
		*threadid[t] = t;
		printf("Creating thread number: %d\n", t);
		if ( error = pthread_create(&threads[t], &attrb, compute_multiplication, (void *)threadid[t])) {
			printf("Failed to create thread: %d\n", t+1);
			exit(1);
		}
	}
	
	pthread_attr_destroy(&attrb);
	for (t=0; t<NUMTHRDS; t++) {
		if(error = pthread_join(threads[t], &status)) {
			printf("Failed to join thread: %d\n", t+1);
			exit(1);
		} else {
			printf("Completed join with thread number: %d with status: %ld\n", t, (long)status);
		}
	}	
	printf("Sum: %f\n", dotstr.sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutexsum);
	exit(0);
	
}	


void *compute_multiplication(void *t)
{
	int i,sum,t_new;
	pthread_t id;

	t_new = *(int *)t;
	sum = 0;
	id = pthread_self();
	for (i=(t_new*dotstr.veclen); i<((t_new*dotstr.veclen) + dotstr.veclen); i++){

		sum += dotstr.a[i] * dotstr.b[i];
		printf("Thread with ID %u. Counted from %d to %d the Sum %f\n", (unsigned)id, (t_new*dotstr.veclen), ((t_new*dotstr.veclen + dotstr.veclen), (float) sum));
	}

	pthread_mutex_lock(&mutexsum);
	dotstr.sum += sum;
	pthread_mutex_unlock(&mutexsum);
	printf("New global value: %f\n", dotstr.sum);
	pthread_exit((void *) 0);
}