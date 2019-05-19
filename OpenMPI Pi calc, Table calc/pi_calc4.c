#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>




	int main (int argc, char *argv[]) {
	int i;
	int N;
	int numtasks;
	int rank;
	int start ,end;
	int rc;


	float pi,pis;

	char *in;


MPI_Status stat;
MPI_Request req;
rc = MPI_Init(&argc,&argv);
	if (rc != MPI_SUCCESS) {
printf ("ERROR Starting MPI program.\n");
MPI_Abort(MPI_COMM_WORLD, rc);
	}
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);


	if(numtasks < 2){
printf("Need at least two tasks in order to proceed \n");
MPI_Abort(MPI_COMM_WORLD,rc);

}
clock_t start1 = clock();

	if (rank == 0){


	if(argc != 2){
printf("No parameter found \n");
exit(0);
}

	else {
in = argv[1];
	for(i=0; i<strlen(in); i++) {
	if (isdigit(in[i]) == 0)  {
printf ("You ve entered invalid data \n");
exit(0);
	}
}
}


N = atoi(argv[1]);

MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
pi=0.0;
start = (rank * N)/numtasks;
end = ((rank + 1) * N)/numtasks;

	float W=1.0/N;
	for (i = start; i < end ; i++) { 

pi+=4*W/(1+(i+0.5)*(i+0.5)*W*W);
 
} 

	for(i=1; i<numtasks; i++){
MPI_Irecv(&pis,1,MPI_FLOAT,i,0,MPI_COMM_WORLD,&req);
MPI_Wait(&req,&stat);
printf("Proccess %d send value: %f \n", i, pis);
pi+=pis;
	}

clock_t end1 = clock();
	double elapsed_time = (end1 - start1)/(double)CLOCKS_PER_SEC;

printf("steps = %d\n pi = %f \n Elapsed time: %.2f.\n", N, pi, elapsed_time);
}

	else {

MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
pi=0.0;
start = (rank * N)/numtasks;
end = ((rank + 1) * N)/numtasks;
	float W=1.0/N;
	for (i = start; i < end ; i++) { 

pi+=4*W/(1+(i+0.5)*(i+0.5)*W*W);
 
}

MPI_Send(&pi,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);

}

MPI_Finalize();


return 0;
}
