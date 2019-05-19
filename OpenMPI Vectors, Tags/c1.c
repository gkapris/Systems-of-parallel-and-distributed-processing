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
	int tag, i, j, b[N], c[10], buff[sizeof(c)], A[10][N], rank, size, nmln, start = 0, steps, row, que;
        char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
        MPI_Status status;
// Elegxos katastasis MPI
        if (MPI_SUCCESS != 0){
                gethostname(tmp, 32);
                printf("Error on computer: %s\n", tmp);
                MPI_Abort(MPI_COMM_WORLD, 0);
        }
// Lipsi timwn tou MPI
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Get_processor_name(name, &nmln);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
// Arxikopoiisi pinakwn
	if(rank == 0){
		initialize_array_random(A);
//		printf("Input 5 integer values for table: \n");
		if(argc < 2 && argc > N+1 ){ 
	                printf("Error on computer: %s\n", tmp);
	                MPI_Abort(MPI_COMM_WORLD, 0);
		}
		for(i=1; i<=N; i++){
			b[i] = atoi(argv[i]);
		}
// Ypologismos oriwn kai apostoli munimatwn stis cpus
		row = (sizeof(A)/sizeof(A[0][0]));
		que = row % size;
		steps = row / size;
		for(i=0;i<size; i++){
	                MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        	        MPI_Send(&steps, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			start += steps;
		}
		if(que!=0){
			steps = size - start;
            MPI_Send(&start, 1, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD);
            MPI_Send(&steps, 1, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD);
		}//end que!=0
	}
		
// Lipsi data gia ylopoiisi dianusmatos

	MPI_Recv(&start, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&steps, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);

	printf("[rank %d] Received %d %d\n",rank,status.MPI_SOURCE,status.MPI_TAG);
	for(i=start; i<(start+steps); i++){
		c[i] = 0;
		for(j=0; j<N; j++){
			c[i] = c[i] + A[i][j] * b[j];
		}
	}
	MPI_Send(&start, steps, MPI_INT, 0, rank, MPI_COMM_WORLD);
	MPI_Send(&c, steps, MPI_INT, 0, rank, MPI_COMM_WORLD);
	
	
	
	
// Lipsi apotelesmatwn
	if(rank==0){
		MPI_Recv(&start, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buff, steps, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		tag = status.MPI_TAG;
		c[tag]= buff[tag];
	}
// Ektipwsi apotelesmatwn
	print_results(b, A, c);
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
