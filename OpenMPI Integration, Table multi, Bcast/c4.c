#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#define M 10
#define N 5
#define K 5
#define L 2

void initialize_array_from_file(float temp[M][N]);
void initialize_arrayB_from_file(float temp[K][L]);

int main(int argc, char *argv[]){
	int i,j,z,status,rank,nprocs,upol,sires,n,mege8os,last,tag,siratemp,count,arxh,lhksh,firsttime;
	double begin, end;
	float time_res;
	float siresflo;
	float arrayA[M][N], arrayB[K][L] ,apotelesma[M][L],tempres[M*L],res[M*L];
	MPI_Status stat;
	MPI_Request req;
	
	status=MPI_Init(&argc,&argv);
	if(status !=0){
		printf("error starting MPI \n");
		MPI_Abort(MPI_COMM_WORLD,status);
	}
	
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(nprocs<2){
		printf("minimum number of proc 2\n");
		MPI_Abort(MPI_COMM_WORLD,status);
	}
	
	if(rank==0){
		begin=MPI_Wtime();
		if(nprocs>M+2){
			nprocs=M+1;
		}
		for(i=0; i<M; i++){
			for(j=0; j<L; j++){
				apotelesma[i][j]=0;
			}

		}
		initialize_array_from_file( arrayA);
		initialize_arrayB_from_file( arrayB);
		
		n=0;upol=M%(nprocs-1);
		if(upol==0){
			sires=M/(nprocs-1);
			mege8os=sires*N;
			for(i=1; i<nprocs; i++){
				MPI_Send(&arrayA[n],mege8os,MPI_FLOAT,i,0,MPI_COMM_WORLD);
				n+=sires;
			}
		}else{
			siresflo=(float)M/(float)(nprocs-1);
			sires=floor(siresflo);
			for(i=1; i<nprocs; i++){
				if(upol > 0 ){
					mege8os=(sires+1)*N;
				}else{
					mege8os=sires*N;
				}	
				MPI_Send(&arrayA[n],mege8os,MPI_FLOAT,i,0,MPI_COMM_WORLD);
			
				if(upol >0){
					n+=sires+1;
					upol--;
				}else{
					n+=sires;
				}		
			}
		}

		for(i=1; i<nprocs; i++){
			MPI_Send(&arrayB,K*L,MPI_FLOAT,i,0,MPI_COMM_WORLD);
		}
	
		upol=M%(nprocs-1);
		firsttime=10;
		for(i=1; i<nprocs; i++){
			n=0;
			if(upol > 0){
				MPI_Recv(&tempres,L*(sires+1),MPI_FLOAT,i,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
				tag=stat.MPI_TAG;
				arxh=tag*(sires+1);
				lhksh=(tag+1)*(sires+1);
				for(j=arxh; j<lhksh; j++){
					for(z=0; z<L; z++){
						apotelesma[j][z]=tempres[n];
						n++;
					}
				}	
	
			}else{
				MPI_Recv(&tempres,L*sires,MPI_FLOAT,i,MPI_ANY_TAG,MPI_COMM_WORLD,&stat);
				tag=stat.MPI_TAG;
				if(firsttime==10){	
					arxh=tag*(sires+1);
					lhksh=arxh+sires;	
				}else{
					arxh=lhksh;
					lhksh=arxh+sires;
				}	
		
				for(j=arxh; j<lhksh; j++){
					for(z=0; z<L; z++){
						apotelesma[j][z]=tempres[n];
						n++;
					}
				}	
				firsttime=0;
			}
			upol--;
		}	
		
		printf("apotelesma: \n");
		for(i=0; i<M; i++){
			for(j=0; j<L; j++){
				printf("%f \t",apotelesma[i][j]);
			}
			printf("\n");
		}
		end=MPI_Wtime();
		time_res=end-begin;
		printf("in %f secs \n",time_res);


		
	}else if(rank>0 && rank<(M+2)){
		if(nprocs>M+2){
			nprocs=M+1;
		}
	
		for(i=0; i<M; i++){
			for(j=0; j<L; j++){
				apotelesma[i][j]=0;
			}
		}

	
		upol=M%(nprocs-1);
		if(upol==0){
			sires=M/(nprocs-1);
			mege8os=sires*N;
			MPI_Recv(&arrayA,mege8os,MPI_FLOAT,0,0,MPI_COMM_WORLD,&stat);
		}else{	
			siresflo=(float)M/(float)(nprocs-1);
			sires=floor(siresflo);
			if(rank < upol+1 ){
				mege8os=(sires+1)*N;
				MPI_Recv(&arrayA,mege8os,MPI_FLOAT,0,0,MPI_COMM_WORLD,&stat);
			}else{
				mege8os=sires*N;
				MPI_Recv(&arrayA,mege8os,MPI_FLOAT,0,0,MPI_COMM_WORLD,&stat);
			}					
		}
		MPI_Recv(&arrayB,K*L,MPI_FLOAT,0,0,MPI_COMM_WORLD,&stat);
		if(rank < upol+1 ){
			for(i=0; i<=sires; i++){
				for(j=0; j<L; j++){
					for(z=0; z<N; z++){	
						apotelesma[i][j]+=arrayA[i][z]*arrayB[z][j];
					}
				}		
			}
			MPI_Send(&apotelesma,(sires+1)*L,MPI_FLOAT,0,rank-1,MPI_COMM_WORLD);	
		}else{
			for(i=0; i<sires; i++){
				for(j=0; j<L; j++){
					for(z=0; z<N; z++){	
						apotelesma[i][j]+=arrayA[i][z]*arrayB[z][j];
					}
				}		
			}
			MPI_Send(&apotelesma,sires*L,MPI_FLOAT,0,rank-1,MPI_COMM_WORLD);
		}
	}
	
	MPI_Finalize();
	return(0);
}

void initialize_array_from_file (float temp[M][N])
{
	FILE *fp;
	int i,j;

	fp= fopen("arrayA.dat","r");
	if (fp == NULL){
		printf("error tring to open for read array.dat \n");
		exit(0);
	}
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
		fscanf(fp,"%f",&temp[i][j]);
		}
	}


}


void initialize_arrayB_from_file (float temp[K][L])
{
	FILE *fp;
	int i,j;

	fp= fopen("arrayB.dat","r");
	if (fp == NULL){
		printf("error tring to open for read array.dat \n");
		exit(0);
	}
	for(i=0; i<K; i++){
		for(j=0; j<L; j++){
		fscanf(fp,"%f",&temp[i][j]);
		}
	}
}

