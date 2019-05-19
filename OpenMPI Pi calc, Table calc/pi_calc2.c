#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int i, N = 0;
	if(argc < 2){
		printf("No input\n");
		return 0;
	}else{
		N = atoi(argv[1]);
	}
	if(argc < 1 && argc > 2 ){ printf("Error\n");  return 0;}
	float pi, W = 1.0/N;
	pi = 0.0;
	for (i=0;i<N;i++) pi += 4*W/(1+(i+0.5)*(i+0.5)*W*W);
	printf ("Value of pi is: %f\n", pi);

	return 0;
}
