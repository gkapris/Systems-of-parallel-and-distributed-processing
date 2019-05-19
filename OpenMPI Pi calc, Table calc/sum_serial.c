#include <stdio.h>
#define SIZE 50000

main (int argc, char *argv[])
{
	int i, sum, Tsum, data[SIZE];
	for(i=0; i<SIZE; i++){data[i] = i + 1;}
	Tsum =0;
	for(i=0; i<SIZE; i++){ Tsum = Tsum + data[i];}
	printf("Total Sum %d\n", Tsum);
	return 0;
}
