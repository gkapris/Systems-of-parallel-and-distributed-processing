#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define pi 3.141592
#define kostos_xal 0.1
#define SIZE 20000


int main(int argc, char *argv[]){



time_t start, end;

float res;
float a[SIZE],a1[SIZE],emvadon[SIZE],xwritikotita[SIZE],kostos[SIZE],xwritikotita_kostos[SIZE];
float kemvadon[SIZE],kxwritikotita[SIZE],kkostos[SIZE],kxwritikotita_kostos[SIZE];
float lkemvadon[SIZE],lkxwritikotita[SIZE],lkkostos[SIZE],lkxwritikotita_kostos[SIZE];
float lemvadon[SIZE],lxwritikotita[SIZE],lkostos[SIZE],lxwritikotita_kostos[SIZE];
float vima=0.001;

int i,chunksize,status,nprocs,rank;

FILE *ofp;

MPI_Status stat;
MPI_Request req;

status=MPI_Init(&argc, &argv);

	if(status !=0){
printf("Error_starting_MPI \n");
MPI_Abort(MPI_COMM_WORLD,status);
}


MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

chunksize=SIZE/nprocs;

	if(rank==0){

start=clock();
a[0]=1;
for(i=1; i<19001; i++){
a[i]=a[i-1]+vima;
	
}

	}
MPI_Scatter(&a,chunksize,MPI_FLOAT,&a1,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);

//------------------------------kuvos-------------------------------------------
for(i=0; i<chunksize; i++){
lemvadon[i]=6*pow(a1[i],2);
}


for(i=0; i<chunksize; i++){
lxwritikotita[i]=pow(a1[i],3);
}


for(i=0; i<chunksize; i++){
lkostos[i]=kostos_xal*lemvadon[i]*10000;
}


for(i=0; i<chunksize; i++){
lxwritikotita_kostos[i]=lxwritikotita[i]/lkostos[i];
}




for(i=0; i<chunksize; i++){
lkemvadon[i]=4*pi*pow(a1[i],2);
}


for(i=0; i<chunksize; i++){
lkxwritikotita[i]=4/3*pi*pow(a1[i],3);
}


for(i=0; i<chunksize; i++){
lkkostos[i]=kostos_xal*lkemvadon[i]*10000;
}


for(i=0; i<chunksize; i++){
lkxwritikotita_kostos[i]=lkxwritikotita[i]/lkkostos[i];
}



MPI_Gather(&lemvadon,chunksize,MPI_FLOAT,&emvadon,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lxwritikotita,chunksize,MPI_FLOAT,&xwritikotita,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lkostos,chunksize,MPI_FLOAT,&kostos,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lxwritikotita_kostos,chunksize,MPI_FLOAT,&xwritikotita_kostos,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);




MPI_Gather(&lkemvadon,chunksize,MPI_FLOAT,&kemvadon,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lkxwritikotita,chunksize,MPI_FLOAT,&kxwritikotita,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lkkostos,chunksize,MPI_FLOAT,&kkostos,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Gather(&lkxwritikotita_kostos,chunksize,MPI_FLOAT,&kxwritikotita_kostos,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);


if(rank==0){

ofp=fopen("results.txt","w");
fprintf(ofp,"gia ton kivo \n");
for(i=0; i<19001; i++){
fprintf(ofp, "akmi: %f  emvadon: %f xwritikotita: %f kostos: %f xwritikotita/kostos: %f \n",a[i],emvadon[i],xwritikotita[i],kostos[i],xwritikotita_kostos[i]);
	}

fprintf(ofp,"gia thn sfera \n");
for(i=0; i<19001; i++){
fprintf(ofp, "aktina: %f  emvadon: %f xwritikotita: %f kostos: %f xwritikotita/kostos: %f \n",a[i],kemvadon[i],kxwritikotita[i],kkostos[i],kxwritikotita_kostos[i]);
        }



fclose(ofp);

end=clock();
res=(((float)end-(float)start)/1000000.0F)*1000;;
printf("Finished at %d msecs\n",(int)res);


}




MPI_Finalize();

return(0);
}
