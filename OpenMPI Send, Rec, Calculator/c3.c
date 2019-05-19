#include <stdio.h>
#include <mpi.h>
int main (int argc, char* argv[])
{
	int rank, count;
	MPI_Status status;
	double msg1[50], msg2[50];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank==0) {
		MPI_Send(&msg1, 50, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&msg2, 10, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
		printf("Message sent from rank%d\n",rank );
	}else if(rank==1){
		MPI_Recv(&msg2, 50, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&msg1, 10, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		printf("Rank%d received message\n",rank );
	}
	MPI_Finalize();
	return 0;
}
