#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define N 5

MPI_Status status;
int main (int argc, char *argv[]) {
// Arxikopoiisi
    MPI_Init(&argc, &argv);
	srand(time(NULL));
	int i, j, b[N], c[10], A[10][N], rank, size, nmln;
    char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
// Elegxos katastasis MPI
    if (MPI_SUCCESS != 0){
        gethostname(tmp, 32);
        printf("Error on computer: %s\n", tmp);
        MPI_Abort(MPI_COMM_WORLD, 0);
    }
//Lipsi timwn tou MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &nmln);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
// Eisagwgi pinaka
	if(rank == 0){
		initialize_array_random(A);
		if(argc < 1){ printf("Error\n");  return 0;}
		for(i=0; i<=N; i++){
			b[i] = atoi(argv[i+1]);
		}

// Ypologismos dianusmatos
		for(i=0; i<10; i++){
			c[i] = 0;
			for(j=1; j<N; j++){
			c[i] = c[i] + A[i][j] * b[j];
		}
	}
		print_results(b, A, c);
	}
	MPI_Finalize();
	return 0;
}
// Sunartisi arxikopoiisis pinaka apo arxeio
int initialize_array_random(int B[10][N]){
	FILE *fp;
	int i, j;
	fp=fopen("/zstorage/home/ictest00509/lab/lab6/array.dat","r");
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
