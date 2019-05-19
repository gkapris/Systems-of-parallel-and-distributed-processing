#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

        printf("Hello World! My rank is %d and the size of communicator %d!\n", rank, size);

	MPI_Finalize();
	return 0;

}

