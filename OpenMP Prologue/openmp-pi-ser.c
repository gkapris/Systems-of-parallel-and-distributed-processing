#include <stdio.h>
#define STEPS 1000000

int main (int argc, char *argv[]) {
	
	int i;
	double start, total, step, x, sum, pi = 0;
	start = omp_get_wtime();
	step = 1.0 / STEPS;
	
	for (i=0; i<STEPS; i++){
		x= (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	
	pi= step * sum;
	
	total = omp_get_wtime() - start;
	printf("Time = %f\nPi = %f\n", total, pi);
	return 0;
	
}