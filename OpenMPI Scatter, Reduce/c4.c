#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

int main(){
// Arxikopoiisi
	srand(time(NULL));
	int i, j, b[N], c[10], A[10][N];
	initialize_array_random(A);
// Eisagwgi pinaka
	printf("Input 5 integer values for table: \n");
	for(i=0; i<N; i++){
		scanf("%d\n", &b[i]);
	}
// Ypologismos dianusmatos
	for(i=0; i<10; i++){
		c[i] = 0;
		for(j=1; j<N; j++){
			c[i] = c[i] + A[i][j] * b[j];
		}
	}

	print_results(b, A, c);
	return 0;
}
// Sunartisi arxikopoiisis pinaka apo arxeio
int initialize_array_random(int B[10][N]){
	FILE *fp;
	int i, j;
	fp=fopen("array.dat","r");
	if(fp==NULL){
		printf("Error at file reading\n");
		exit(0);
	}
	for(i=0;i<10;i++){
		for(j=0;j<N;j++){
			fscanf(fp,"%d",&B[i][j]);
		}
	}
}
//Ektupwsi apotelesmatwn
void print_results(int b[N], int A[10][N], int c[N]){
	int i, j;
	printf("O pinakas timwn einai: \n");
	for(i=1;i<10;i++){
		for(j=1;j<N;j++){
			printf("%d, ",A[i][j]);
		}
	}
	printf("\n");
	printf("\nTo dianusma apoteleitai:\n");
	for(i=0;i<N;i++){printf("%d, ", b[i]);}
	printf("\n");
	printf("\nTo apotelesma apoteleitai:\n");
	for(i=0;i<N;i++){printf("%d, ", c[i]);}
	printf("\n");
}
