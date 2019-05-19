#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	int input, rank, nmln, size,sent, recv, count;
	char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status;

	if (MPI_SUCCESS != 0){
	gethostname(tmp, 32);
	printf("Error on processor: %s\n", tmp);
	MPI_Abort(MPI_COMM_WORLD, 0);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &nmln);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	
	if (size<2){
		printf("Minimum 2 pricesses are required \n");
		MPI_Abort(MPI_COMM_WORLD, 0);
	}
	
	if(rank==0){
	      	if(argc<2){
        	    printf("No parameter \n");
				MPI_Abort(MPI_COMM_WORLD, 0);
		}else{
			input = atoi(argv[1]);
	    }
		if(input<0 && input >99) MPI_Abort(MPI_COMM_WORLD, 0);
		sent = input;
	}
	
	if(rank==0)
	{
		MPI_Send(&sent, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
/*		MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
		printf("(rank%d) (%s) Send: %s -> Received: %s\n Count: %d\n", rank, name, sent, recv, count);
		
*/	}else if(rank > 0 && rank != size -1){
		MPI_Recv(&recv, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
		sent = rank + recv;
		MPI_Send(&sent, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
		printf("(rank%d) (%s) Received -> %d Sent -> %d\n Count = %d\n", rank, name, recv, sent, count);		
		
	}else if(rank == size -1){
		MPI_Recv(&recv, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
		sent = rank + recv;
		MPI_Send(&sent, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("(rank%d) (%s) Received -> %d Sent -> %d\n Count = %d\n", rank, name, recv, sent, count);
		
	}else{
		printf("Nothing to do at nod %s\n", name);
	}
	
	if(rank == 0){
		MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
		printf("(rank%d) (%s) Received -> %d Sent -> %d\n Count = %d\n", rank, name, recv, sent, count);
	}



	MPI_Finalize();
	return 0;
}
