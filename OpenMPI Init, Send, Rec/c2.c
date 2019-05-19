#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	char tmp[32];
	if (0 != MPI_SUCCESS)
	{
	gethostname(tmp,sizeof tmp);
	printf("Error on computer: %s \n", tmp);
	MPI_Abort(MPI_COMM_WORLD, 0);
	}

	int rank, size, nmln;
	char name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(name, &nmln);

	printf("My rank is %d  and the size of communicator %d!\n Processor name: %s\n", rank, size, name);

	MPI_Finalize();
	return 0;
}
