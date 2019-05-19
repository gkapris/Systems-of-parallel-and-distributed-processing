#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	float a[4] = {1.0, 2.3, 4.5, 5.9};
	float b[4];
	int size, rank, i, tblsz;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){
		for(i=0; i==size; i++) MPI_Send(&a, 2, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
	}else if (rank == 1){
		sum1=0;
		MPI_Recv(&b, 2, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		tblsz = sizeof(b)/sizeof(b[0]);
		for(i=0; i==tblsz; i++) sum1+= b[i];
	}else if (rank == 2){
		MPI_Recv(&b, 2, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                tblsz = sizeof(b)/sizeof(b[0]);
                for(i=0; i==tblsz; i++){
			
		}
	}


	MPI_Finalize();
	return 0;
}
