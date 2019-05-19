#include <stdio.h>
#include <omp.h>

int main (){
	
	int i, a[100], sum = 0;
	
	for (i=0;i<100;i++) a[i]=i;
	
	for (i=0;i<100;i++) sum += a[i];
	
	printf("Sum is: %d\n", sum);	
	
	return 0;
}