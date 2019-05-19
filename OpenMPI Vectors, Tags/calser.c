
// compile with: gcc calser.c -o calser -lm

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pi 3.141592
#define kostos_xal 0.1

int main(){
//Arxikopoiisi
	time_t start, end;
	float a[20000],emvadon[20000],xwritikotita[20000],kostos[20000],xwritikotita_kostos[20000];
	float step=0.001;
	int i;
	FILE *ofp;
	start=clock();
	a[0]=1;
// Ypologismos Kubou
	for(i=1; i<19001; i++){
		a[i]=a[i-1]+step;
	}
	for(i=0; i<19001; i++){
		emvadon[i]=6 * pow (a[i],2);
	}
	for(i=0; i<19001; i++){
		xwritikotita[i] = pow (a[i],3);
	}
	for(i=0; i<19001; i++){
		kostos[i]=kostos_xal*emvadon[i]*10000;
	}
	for(i=0; i<19001; i++){
		xwritikotita_kostos[i]=xwritikotita[i]/kostos[i];
	}
//Apothukeusi sto arxeio
	ofp=fopen("results.txt","w");
	fprintf(ofp,"gia ton kivo \n	akmi		emvadon		xwritikotita		xwritikotita/kostos \n");
	for(i=0; i<19001; i++){
		fprintf(ofp, "%f		%f		%f		%f		%f \n",a[i],emvadon[i],xwritikotita[i],kostos[i],xwritikotita_kostos[i]);
	}
//Ypologismos Sfairas
	fprintf(ofp,"gia thn sfera \n	akmi		emvadon		xwritikotita		xwritikotita/kostos \n");
	for(i=0; i<19001; i++){
		emvadon[i]=4*pi*pow(a[i],2);
	}
	for(i=0; i<19001; i++){
		xwritikotita[i]=4/3*pi*pow(a[i],3);
	}
	for(i=0; i<19001; i++){
		kostos[i]=kostos_xal*emvadon[i]*10000;
	}
	for(i=0; i<19001; i++){
		xwritikotita_kostos[i]=xwritikotita[i]/kostos[i];
	}
	for(i=0; i<19001; i++){
		fprintf(ofp, "%f		%f		%f		%f		%f \n",a[i],emvadon[i],xwritikotita[i],kostos[i],xwritikotita_kostos[i]);
	}

	fclose(ofp);
	end=clock();
	printf("Finished at %.3f secs\n",((double)(end - start) / CLOCKS_PER_SEC));
	
	return(0);	
}

