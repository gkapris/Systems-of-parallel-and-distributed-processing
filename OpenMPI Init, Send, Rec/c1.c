#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	if (0 != MPI_SUCCESS)
	{
		MPI_Abort(MPI_COMM_WORLD, 0);
		printf("MPI Error");
	}

	int rank, size, nmln;
	char name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(name, &nmln);

        printf("Hello World! My rank is %d  and the size of communicator %d!\n Processor name: %s\n", rank, size, name);

	MPI_Finalize();
	return 0;
}
