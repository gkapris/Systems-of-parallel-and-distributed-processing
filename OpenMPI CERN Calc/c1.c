
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define S 25000
FILE *ofp;
int main(int argc, char *argv[]){

int status,utime,i,z,j,rank[2],nprocs,upol,chunksize,count,color,tag,megproig,nprocs1,arxh,lhksh,sum,gramena,gramenasnd;
int epitsug[S];

long int ltime;

double begin, end;
float time_res;

float cords[S][3],cords1[S][3];
float apot[S][3],apotel[S][3];

MPI_Comm comm,intercomm;
MPI_Status stat;
MPI_Request req;

status=MPI_Init (&argc, &argv);

if(status !=0){
	printf("error starting MPI \n");
	MPI_Abort(MPI_COMM_WORLD,status);
}


MPI_Comm_rank (MPI_COMM_WORLD, &rank[0]);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);


if(nprocs<6){
	printf("minimum number of proc 6\n");
	 MPI_Abort(MPI_COMM_WORLD,status); 
}



upol=S%(nprocs-1);

if(upol != 0){
	do{
	nprocs--;
	upol=S%(nprocs-1);}
	while(upol !=0);
	//printf("run with %d number of procs \n",nprocs);
	// MPI_Abort(MPI_COMM_WORLD,status); 
	
}

	

if((rank[0]==0) || rank[0]>=nprocs){
	color=0;
	}
else{
	color=1;
	}

if(rank[0]==0){
	ltime = time(NULL);
	utime = (unsigned int) ltime/2;
	srand(utime);
	for(i=0;i<S;i++){
		cords[i][0]=(float)34*rand()/(RAND_MAX-1);
		cords[i][1]=(float)34*rand()/(RAND_MAX-1);
		cords[i][2]=(float)34*rand()/(RAND_MAX-1);
	}

	ofp=fopen("results_cern.txt","w");

	fprintf(ofp,"apotelesmata \n");

}


chunksize=S/(nprocs-1);



MPI_Comm_split(MPI_COMM_WORLD,color,rank[0],&comm);
MPI_Comm_rank (comm, &rank[1]);
MPI_Comm_size (comm, &nprocs1);

if(rank[0]==0){
	MPI_Intercomm_create(comm,0,MPI_COMM_WORLD,1,99,&intercomm);
	//MPI_Send(&temp,10,MPI_INT,rank[1],0,intercomm);

}
else if((rank[0]>0) || (rank[0]<nprocs)){
	MPI_Intercomm_create(comm,0,MPI_COMM_WORLD,0,99,&intercomm);
	//MPI_Recv(&temp,10,MPI_INT,rank[1],0,intercomm,&stat);
}


if(color==0){
	if(rank[1]==0){
		MPI_Send(&cords,3*S,MPI_FLOAT,rank[1],0,intercomm);
	}
}
else{	
	if(rank[1]==0){	
	MPI_Recv(&cords,3*S,MPI_FLOAT,rank[1],0,intercomm,&stat);
	}
}	

if(color==1){

MPI_Scatter(&cords,chunksize*3,MPI_FLOAT,&cords1,chunksize*3,MPI_FLOAT,0,comm);

if(rank[1]==0){
begin=MPI_Wtime();
}
j=0;
	for(i=0; i<chunksize; i++){
		if(cords1[i][0]>=12 && cords1[i][0]<=30){
			if(cords1[i][1]>=12 && cords1[i][1]<=30){
				if(cords1[i][2]>=12 && cords1[i][2]<=30){
					apot[j][0]=cords1[i][0];
					apot[j][1]=cords1[i][1];
					apot[j][2]=cords1[i][2];
					j++;
				}
			}
		}			

	}	
	

	if(rank[1]==0){
	end=MPI_Wtime();
	time_res=end-begin;
	printf("xronos epeksergasias: %f secs \n",time_res);
	}
	
	
	if(rank[1] ==0){
	gramena=0;
	MPI_Send(&j,1,MPI_INT,rank[1]+1,0,comm);
	MPI_Recv(&sum,1,MPI_INT,nprocs1-1,0,comm,&stat);
	}
	else if (rank[1]>0 && rank[1]<(nprocs1-1)){
	MPI_Recv(&gramena,1,MPI_INT,rank[1]-1,0,comm,&stat);
	gramenasnd=gramena+j;
	MPI_Send(&gramenasnd,1,MPI_INT,rank[1]+1,0,comm);
	}
	else {
	MPI_Recv(&gramena,1,MPI_INT,rank[1]-1,0,comm,&stat);
	sum=gramena+j;
	MPI_Send(&sum,1,MPI_INT,0,0,comm);
	}
	

	if(rank[1]!=0){
		MPI_Send(&j,1,MPI_INT,0,rank[1],comm);
	}
	else{
		epitsug[0]=j;
		for(i=1; i<nprocs1; i++){
			MPI_Recv(&j,1,MPI_INT,i,MPI_ANY_TAG,comm,&stat);
			tag=stat.MPI_TAG;
			epitsug[tag]=j;
		}
	}
	
	//printf("rank %d exei %d gramena \n",rank[1],gramena);
	
	if(rank[1]!=0){
		MPI_Send(&apot,j,MPI_FLOAT,0,rank[1],comm);
	}
	else{
		z=0;
		for(i=0; i<j; i++){
			apotel[i][0]=apot[i][0];
			apotel[i][1]=apot[i][1];
			apotel[i][2]=apot[i][2];
		
		}
		
		for(i=1; i<nprocs1; i++){
			MPI_Recv(&apot,chunksize,MPI_FLOAT,i,MPI_ANY_TAG,comm,&stat);
			tag=stat.MPI_TAG;
			
		/*	lhksh=epitsug[tag];
			for(i=0; i<lhksh; i++){
				printf("%f ,%f , %f \n",apot[i][0],apot[i][1],apot[i][2]);
			}
		*/	//printf("eptisug is %d\n",epitsug[4]);
			arxh=0;
			for(z=0; z<tag; z++){
				arxh+=epitsug[z];
			}
			lhksh=arxh+epitsug[tag];
			z=0;
			for(j=arxh; j<lhksh; j++){
			apotel[j][0]=apot[z][0];
			apotel[j][1]=apot[z][1];
			apotel[j][2]=apot[z][2];
			z++;
			}
			
			
			
		}
			
	}
	
	
	

}

if(rank[0]==1){
	MPI_Send(&apotel,3*lhksh,MPI_FLOAT,rank[1],0,intercomm);
	MPI_Send(&epitsug,nprocs1,MPI_INT,rank[1],0,intercomm);
}	


if(rank[0]==0){
	
	MPI_Recv(&apotel,3*S,MPI_FLOAT,rank[1],0,intercomm,&stat);
	MPI_Get_count(&stat,MPI_INT,&count);
	MPI_Recv(&epitsug,nprocs-1,MPI_INT,rank[1],0,intercomm,&stat);

	
	
	for(i=0; i<count/3; i++){
		fprintf(ofp, " %f , %f , %f \n",apotel[i][0],apotel[i][1],apotel[i][2]);
	}
	for(i=0; i<nprocs-1; i++){
		fprintf(ofp,"from rank %d \t %d for %d \n",i,epitsug[i],chunksize);	
	}	
	
	fclose(ofp);	
	printf("done!! \n");
	

}


MPI_Finalize();

return(0);


}
