#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	int x, rank, nmln, size, bound ,count;
	char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
	char sent[32]="xx";
	char recv[32];
	MPI_Status status;

	if (MPI_SUCCESS != 0){
	gethostname(tmp, 32);
	if (x==0) printf("Error on processor: %s\n", tmp);
	MPI_Abort(MPI_COMM_WORLD, 0);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &nmln);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0)
	{
		MPI_Send(&sent, 8, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv, 8, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD, &status);
                MPI_Get_count(&status, MPI_INT, &count);
                if(count != 0){
                        stpcpy(sent,recv);
                        strcat(sent,"*");
                        strcat(sent,"\0");
                }
		printf("(rank%d) (%s) Send: %s -> Received: %s\n Count: %d\n", rank, name, sent, recv, count);
	}
	else if(rank==1)
	{
		MPI_Recv(&recv, 8, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD, &status);
                MPI_Get_count(&status, MPI_INT, &count);
		stpcpy(sent,recv);
		strcat(sent,"+");
		strcat(sent,"\0");
		MPI_Send(&sent, 8, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD);
		printf("(rank%d) (%s) Send: %s -> Received: %s\n Count: %d\n", rank, name, sent, recv, count);
	}
//	else
//	{
//		printf("Nothing to do at nod %s\n", name);
//	}

	MPI_Finalize();
	return 0;
}
