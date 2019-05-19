#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){

int arxh,lhksh,status,i, N,rank,nprocs;
float part_pi=0,pi=0,W=1.0/N;

int part_size;
int data_size;


MPI_Status stat;
MPI_Request req;


status=MPI_Init(&argc, &argv);

	if(status !=0){
printf("Error_starting_MPI \n");
MPI_Abort(MPI_COMM_WORLD,status);
}


MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);



int *sendbuff, *recvbuff;


	if(nprocs<2){
printf("Minimum_Number_of_proc 2 \n");
MPI_Abort(MPI_COMM_WORLD,status);

}




	if(argc==1){
printf("Den_dwthike_parametros! \n");
MPI_Abort(MPI_COMM_WORLD,status);

}




N=atoi(argv[1]);
part_size=(N+1)/nprocs;
data_size=N+1;
recvbuff=(int*)malloc(part_size*sizeof(int));


	if (rank==0){
sendbuff=(int*)malloc(data_size*sizeof(int));

for(i=0; i<=N; i++){
sendbuff[i]=i;
}

}


MPI_Scatter(sendbuff,part_size,MPI_INT,recvbuff,part_size,MPI_INT,0,MPI_COMM_WORLD);

W=1.0/N;
for(i=0; i<part_size; i++){
part_pi+=4*W/(1+(recvbuff[i]+0.5)*(recvbuff[i]+0.5)*W*W);

}



MPI_Reduce(&part_pi,&pi,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);


	if(rank==0){
printf("pi_is: %f  \n",pi);
}





MPI_Finalize();



return (0);}


