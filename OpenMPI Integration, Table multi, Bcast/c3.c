#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define M 10
#define N 5
#define K 5
#define L 2

void initialize_array_from_file(float temp[M][N]);
void initialize_arrayB_from_file(float temp[K][L]);

int main(){
	int i,j,z;
	float arrayA[M][N], arrayB[K][L] ,apotelesma[M][L];
	float time_res;
	double begin, end;
	
	begin=MPI_Wtime();
	for(i=0; i<M; i++){
		for(j=0; j<L; j++){
			apotelesma[i][j]=0;
		}
	}
	
	initialize_array_from_file( arrayA);
	initialize_arrayB_from_file( arrayB);
	for(i=0; i<M; i++){
		for(j=0; j<L; j++){
			for(z=0; z<N; z++){	
				apotelesma[i][j]+=arrayA[i][z]*arrayB[z][j];
			}
		}		
	}


	printf("\n Apotelesma: \n");
	for(i=0; i<M; i++){
		for(j=0; j<L; j++){
			printf("%F \t",apotelesma[i][j]);
		}
		printf("\n");
	}
	end=MPI_Wtime();
	time_res=end-begin;
	printf("ended in %f secs \n",time_res);
	
	return(0);
}

void initialize_array_from_file (float temp[M][N])
{
	FILE *fp;
	int i,j;

	fp= fopen("arrayA.dat","r");
	if (fp == NULL){
		printf("error tring to open for read array.dat \n");
		exit(0);
	}
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
		fscanf(fp,"%f",&temp[i][j]);
		}
	}
}


void initialize_arrayB_from_file (float temp[K][L])
{
	FILE *fp;
	int i,j;

	fp= fopen("arrayB.dat","r");
	if (fp == NULL){
		printf("error tring to open for read array.dat \n");
		exit(0);
	}
	for(i=0; i<K; i++){
		for(j=0; j<L; j++){
		fscanf(fp,"%f",&temp[i][j]);
		}
	}
}

