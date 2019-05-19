#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	int worldsize;
	MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
	int worldrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &worldrank);
	char processornm[MPI_MAX_PROCESSOR_NAME];
	int namelen;
	MPI_Get_processor_name(processornm, &namelen);
	printf("Hello world from processor %s, rank %d out of %d processors\n", processornm, worldrank, worldsize);
	MPI_Finalize();

	return 0;
}

