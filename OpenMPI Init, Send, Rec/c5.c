#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	int x, rank, nmln, size, bound;
	int count[2] = {0,0};
	char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
	char sent[32]="xx";
	char recv[32];
	MPI_Status status;

	if (MPI_SUCCESS != 0){
	gethostname(tmp, 32);
	if (x==0) printf("Error on computer: %s\n", tmp);
	MPI_Abort(MPI_COMM_WORLD, 0);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &nmln);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	bound = sizeof(sent)/sizeof(sent[0]);
	if(rank==0)
	{
		MPI_Send(&sent, bound, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv, bound, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
		if(count != 0){
			stpcpy(sent,recv);
			strcat(sent,"*");
			strcat(sent,"\0");
		}
		printf("Message 0 sent: %s -> Message 0 received: %s\n",sent,recv);
		count[rank]++;
	}
	else if(rank==1)
	{
		MPI_Recv(&recv, bound, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		stpcpy(sent,recv);
		strcat(sent,"+");
		strcat(sent,"\0");
		MPI_Send(&sent, bound, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		printf("Message 1 sent: %s -> Message 1 received: %s\n",sent,recv);
		count[rank]++;
	}
//	else
//	{
//		printf("Nothing to do at nod %s\n", name);
//	}

	MPI_Finalize();
	return 0;
}
