#include <omp.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	
	int tid, nthreads;
	
	#pragma omp parallel
	{
		tid = omp_get_thread_num();
		printf("Hello world from thread %d\n", tid);
		
		if (tid == 0){
			nthreads = omp_get_num_threads();
			printf("There are %d threads \n", nthreads);
		}
	}
	return 0;
}