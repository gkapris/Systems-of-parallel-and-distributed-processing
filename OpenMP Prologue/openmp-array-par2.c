#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[]){
	
	int i, a[100], sum = 0;
	
	#pragma omp for reduction(+:sum)
	for (i=0;i<100;i++){
		a[i]=i;
		sum += a[i];
		
		int tid = omp_get_thread_num();
		if(tid ==0 && i==0){
			int threads = omp_get_num_threads();
			printf("There are %d threads\n", threads);
		}
	}
	
	printf("Sum is: %d\n", sum);	
	
	return 0;
}


