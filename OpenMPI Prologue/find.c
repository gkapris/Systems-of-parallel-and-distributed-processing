#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	char nm[MPI_MAX_PROCESSOR_NAME];
	int ln;
	MPI_Get_processor_name(nm, &ln);

	printf("Processors name is: %s, witn %d/n", nm, ln);

	MPI_Finalize();
	return 0;
}
