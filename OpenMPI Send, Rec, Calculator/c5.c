#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
// Arxikopoiisi toy MPI kai metablitwn pou tha xrisimopoiisoyme sto programma
	MPI_Init(&argc, &argv);
	int i, rank, nmln, size;
	float result = 0.0;
	float a[4] = {1.0, 2.3, 4.5, 5.9};
	float b[4];
	char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status;
	
	
// Elegxos katastasis MPI
	if (MPI_SUCCESS != 0){
		gethostname(tmp, 32);
		printf("Error on computer: %s\n", tmp);
		MPI_Abort(MPI_COMM_WORLD, 0);
	}
	
//Lipsi timwn tou MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &nmln);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
// Diaxeirisi twn munimatwn sto MPI
	if(rank == 0){
		for(i=1; i<=4; i++){
			MPI_Send(&a, 4, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
		}
		
	}else if (rank == 1){
		MPI_Recv(&b, 4, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		float sum = 0;
		for(i=0; i<sizeof(b); i++){
			sum = sum + b[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		
	}else if (rank == 2){
		MPI_Recv(&b, 4, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		float max = b[0];
        for(i=1; i<sizeof(b); i++){
			if(max < b[i]) max = b[i];
        }
		MPI_Send(&max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		
	}else if (rank == 3){
		MPI_Recv(&b, 4, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
		float min = b[0];
        for(i=0; i<sizeof(b); i++){
			if(min > b[i]) min = b[i];
        }
		MPI_Send(&min, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
	}else if (rank == 4){
		MPI_Recv(&b, 4, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
        float multi = 1;
		for(i=0; i<sizeof(b); i++){
            multi = multi * b[i];
        }
		MPI_Send(&multi, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		
	}else {
		printf("Nothing to do at node %s", name);
	}
	
	if(rank == 0){
			MPI_Recv(&result, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
			printf("Summarize of array is: %f\n", result);
			MPI_Recv(&result, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &status);
			printf("Max value of array is: %f\n", result);
			MPI_Recv(&result, 1, MPI_FLOAT, 3, 0, MPI_COMM_WORLD, &status);
			printf("Min value of array is: %f\n", result);
			MPI_Recv(&result, 1, MPI_FLOAT, 4, 0, MPI_COMM_WORLD, &status);
			printf("Multiplier of array is: %f\n End of job\n", result);
	}
	
	
//Telos programmatos
	MPI_Finalize();
	return 0;
}
