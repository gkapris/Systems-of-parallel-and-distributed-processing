#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>


int main(int argc, char *argv[]){
	int start,the_end,status,i, N=512,rank,nprocs;
	float part_pi=0,pi=0,W=1.0/N;
	MPI_Status stat;
	MPI_Request req;
	pi=0.0;
	status=MPI_Init(&argc, &argv);
	if(status !=0){
		printf("Error_starting_MPI \n");
		MPI_Abort(MPI_COMM_WORLD,status);
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int *sendbuff, *recvbuff;
	if(nprocs<2){
		printf("Minimum_number_of_proc_2 \n");
		MPI_Abort(MPI_COMM_WORLD,status);
	}
	if(argc<2){
		printf("No input \n");
		MPI_Abort(MPI_COMM_WORLD,status);
	}
	recvbuff=(int*)malloc(1*sizeof(int));
	
	if(rank==0){
		N=atoi(argv[1]);
		sendbuff=(int*)malloc(nprocs*sizeof(int));
		for(i=0; i<nprocs; i++){
		sendbuff[i]=N;
		}
	}
	MPI_Scatter(sendbuff,1,MPI_INT,recvbuff,1,MPI_INT,0,MPI_COMM_WORLD);
	N=recvbuff[0];
	start=rank*N/nprocs;
	the_end=(rank+1)*N/nprocs;
	W=1.0/N;
	
	for(i=start; i<the_end; i++){
		part_pi+=4*W/(1+(i+0.5)*(i+0.5)*W*W);
	}
	
	MPI_Reduce(&part_pi,&pi,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("Value of pi is: %f  \n",pi);
	}
	
	MPI_Finalize();
	return (0);
}