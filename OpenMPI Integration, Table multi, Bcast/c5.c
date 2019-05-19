#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#define M 10
#define N 5
#define K 5
#define L 2

void initialize_array_from_file(float temp[M][N]);
void initialize_arrayB_from_file(float temp[K][L]);

int main(int argc, char *argv[]){

int i,j,z,status,rank,nprocs;
int upol,sires,n,chunksize;
double begin, end;
float time_res;
float siresflo;

float arrayA[M][N], arrayB[K][L] ,apotelesma[M][L],tempres[M*L],res[M*L];


MPI_Status stat;
MPI_Request req;


status=MPI_Init(&argc,&argv); 

		if(status !=0){
printf("error starting MPI \n");
MPI_Abort(MPI_COMM_WORLD,status);

}

MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		if(nprocs<2){
printf("minimum number of proc 2\n");
MPI_Abort(MPI_COMM_WORLD,status); 
}

chunksize=M/nprocs*N;

	for(i=0; i<M; i++){
	for(j=0; j<L; j++){
apotelesma[i][j]=0;
	}
		}


		if(rank==0){
begin=MPI_Wtime();
	
		if(nprocs>M){
nprocs=M;
	}
	

initialize_array_from_file( arrayA);
initialize_arrayB_from_file( arrayB);

	n=0;
	upol=M%nprocs;
	if(upol != 0){
printf("wrong number of procs try 2, 5, 10 for other number use c4 (more stable) \n");
MPI_Abort(MPI_COMM_WORLD,status); 
	}	 
	

MPI_Bcast(&arrayB,K*L,MPI_FLOAT,0,MPI_COMM_WORLD);
		
			
}



MPI_Bcast(&arrayB,K*L,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Scatter(&arrayA,chunksize,MPI_FLOAT,&arrayA,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);

for(i=0; i<chunksize/N; i++){
	for(j=0; j<L; j++){
		for(z=0; z<N; z++){	
apotelesma[i][j]+=arrayA[i][z]*arrayB[z][j];
	}
}	
	
}	

MPI_Gather(&apotelesma,chunksize/N*L,MPI_FLOAT,&apotelesma,chunksize/N*L,MPI_FLOAT,0,MPI_COMM_WORLD);

		if(rank==0){
printf("apotelesma: \n");
for(i=0; i<M; i++){
	for(j=0; j<L; j++){
printf("%f \t",apotelesma[i][j]);
		}
printf("\n");
	}		


end=MPI_Wtime();
time_res=end-begin;
printf("in %f secs \n",time_res);	
}


MPI_Finalize();

return(0);
}

void initialize_array_from_file (float temp[M][N])
{
FILE *fp;
int i,j;
fp= fopen("arrayA.dat","r");
		if (fp == NULL){
printf("error trying to open for read array.dat \n");

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


