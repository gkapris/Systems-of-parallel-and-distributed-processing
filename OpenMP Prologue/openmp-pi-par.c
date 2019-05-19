#include <stdio.h>
#include <omp.h>
#define STEPS 1000000

int main (int argc, char *argv[]) {
	int i, tid;
	double start, total, step, x, sum, pi = 0;
	start = omp_get_wtime();
	step = 1.0 / STEPS;
	
	#pragma omp parallel for reduction(+:sum) private(x)
	for (i=0; i<STEPS; i++){
		x= (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
		
		int tid = omp_get_thread_num();
		if(tid ==0 && i==0){
			int threads = omp_get_num_threads();
			printf("There are %d threads\n", threads);
		}
	}
	pi= step * sum;	
	total = omp_get_wtime() - start;
	printf("Time = %f\nPi = %f\n", total, pi);
	return 0;
}