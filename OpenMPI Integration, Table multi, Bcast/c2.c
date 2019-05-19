#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


int main(int argc, char *argv[])
{
// Arxikopoiisi
	MPI_Init (&argc, &argv);
	int arraysize, start, end, x1, i, rank, size, nmln;
	float stime, etime,  time, totalsum, step, sum, total_trap, array[10000];
	char tmp[32], name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status;
	MPI_Request request;
	x1=1;
	
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
	
//Diergasia 0
	if(rank == 0){
// Katanomi diergasiwn
		if(argc < 1){ printf("Error\n");  return 0;}
		total_trap = atoi(argv[1]);
		arraysize = total_trap + 1;
		array[0]=x1;
		for(i=1; i<arraysize; i++){
			array[i]=array[i-1]+step;
		}
		MPI_Bcast(&arraysize,1,MPI_INT,0,MPI_COMM_WORLD);
		start=rank*arraysize/size;
		end=(rank+1)*arraysize/size;
		for(i=start; i<end; i++){
			totalsum+=(((3*pow(array[i],2)+1)+(3*pow(array[i+1],2)+1))*step/2);
		}
		MPI_Bcast(&array,arraysize,MPI_FLOAT,0,MPI_COMM_WORLD);
		
// Sullogi kai termatismos
		for(i=1; i<size; i++){
			MPI_Irecv(&sum,1,MPI_FLOAT,i,0,MPI_COMM_WORLD,&request);
			MPI_Wait(&request,&status);
			printf("Process %d send_value %f \n",i,sum);
			totalsum+=sum;
		}
		etime=MPI_Wtime();
		time=etime-stime;
		printf("Result is: %f in %f secs\n",totalsum,time);
		
// Ypoloipes diergasies	
	} else {
		MPI_Bcast(&arraysize,1,MPI_INT,0,MPI_COMM_WORLD);
		start=(rank*arraysize/size);
		end=((rank+1)*arraysize/size);
		MPI_Bcast(&array,arraysize,MPI_FLOAT,0,MPI_COMM_WORLD);
		if(rank != size-1){
			for(i=start; i<end; i++){
				sum+=(((3*pow(array[i],2)+1)+(3*pow(array[i+1],2)+1))*(array[i+1]-array[i])/2);
			}
		}else{
			for(i=start; i<end-1; i++){
				sum+=(((3*pow(array[i],2)+1)+(3*pow(array[i+1],2)+1))*(array[i+1]-array[i])/2);
			}
			MPI_Send(&sum,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);
		}
	}


	MPI_Finalize();
	return 0;
}
