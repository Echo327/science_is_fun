/*Programme:10corps(euler)*/
#include <stdio.h>
#include <math.h>

/*Systemes d'equations differentielles;dr[] à partir de r[]*/
void f(double z[],double dz[],double w[]){
	double G=2.959122e-4,M[10],d[10],d2[10];
	int i,j,k;

	/*Masses des planètes*/
	M[0]=1;/*Soleil*/
	M[1]=1.6600e-7;/*Mercure*/	M[2]=2.4476e-6;/*Venus*/	M[3]=3.0031e-6;/*Terre*/
	M[4]=3.2268e-7;/*Mars*/		M[5]=9.5425e-4;/*Jupiter*/	M[6]=2.8572e-4;/*Saturne*/
	M[7]=4.3643e-5;/*Uranus*/	M[8]=5.1486e-5;/*Neptune*/	M[9]=6.6060e-9;/*Pluton*/

	/*dr de r;accélérations et vitesses à t*/
	for(i=0;i<30;i++){
		dz[i]=z[i+30];/* vitesses */
	}
	for(i=30;i<60;i=i+3){
        /*initialisation d'accélerations*/
		dz[i]=0;
		dz[i+1]=0;
		dz[i+2]=0;
		for(j=0;j<10;j++){
			k=j*3;
			/*Distance inter-planetaire:r*/
			d[j]=((z[i-30]-z[k])*(z[i-30]-z[k]))+((z[i-29]-z[k+1])*(z[i-29]-z[k+1]))+((z[i-28]-z[k+2])*(z[i-28]-z[k+2]));/* r² */
			d2[j]=d[j]*sqrt(d[j]);/* r³ */
			if(d2[j]!=0){	/*somme des contributions d'accelerations*/
				dz[i]=dz[i]- G*(M[j]/d2[j])*(z[i-30]-z[k]);
				dz[i+1]=dz[i+1]- G*(M[j]/d2[j])*(z[i-29]-z[k+1]);
				dz[i+2]=dz[i+2]- G*(M[j]/d2[j])*(z[i-28]-z[k+2]);
			}
			if(i==30){
				w[j+1]=sqrt(d[j]);	/*distance du planète j par rapport au soleil*/
			}
		}
	}
}/*fin:f*/

/*Resolution d'equation differentielle:méthode d'Euler*/
void euler(double r[],double dr[],double dt){
	int i;
	for(i=0;i<60;i++){
		r[i]=r[i]+dt*dr[i];	/*r(t+dt)=r(t)+k1*/
	}
}/*fin:euler*/

int main()
{
	FILE*fich0;
	fich0=fopen("euler10.txt","w");		/*Positions*/
	FILE*fich3;
	fich3=fopen("pe10eu.txt","w");		/*Périhélies*/

	double t,tmin=0,tmax=92000*2,dt=1;	/*en jours*/
	double r[60]/*positions(30) et vitesses(30)*/,dr[60]/*vitesses(30) et accelerations(30)*/;
	int i,j,k;

	/*Conditions initiales(x,y,x,vx,vy,vz)*/
r[0]=-1.6132380e-3;r[1]=-2.3674938e-3;r[2]=-3.4999903e-5;r[30]=6.0453208e-6;r[31]=-1.8980631e-6;r[32]=-1.3060634e-7; /*Soleil*/
r[3]=3.4942761e-01;r[4]=1.0619088e-02;r[5]=-3.1182970e-02;r[33]=-6.4674481e-03;r[34]=2.9372684e-02;r[35]=2.9939160e-03; /*Mercure*/
r[6]=-5.7685710e-01;r[7]=4.2639983e-01;r[8]=3.9039256e-02;r[36]=-1.2159929e-02;r[37]=-1.6321487e-02;r[38]=4.7839154e-04; /*Venus*/
r[9]=6.8900355e-1;r[10]=7.0799513e-1; r[11]=-5.4762805e-5; r[39]=-1.2606830e-2;r[40]=1.1932472e-2; r[41]=-5.3326343e-7;/*Terre*/
r[12]=4.3534005e-01;r[13]=-1.3548686e+00;r[14]=-3.9100527e-02;r[42]=1.3851438e-02;r[43]=5.5002850e-03;r[44]=-2.2479471e-04; /*Mars*/
r[15]=1.8147606e+00;r[16]=4.7059241e+00;r[17]=-6.0234633e-02;r[45]=-7.1329432e-03;r[46]=3.0767709e-03;r[47]=1.4683761e-04; /*Jupiter*/
r[18]=-8.2319838e+00;r[19]=-5.2651142e+00;r[20]=4.1915711e-01;r[48]=2.7027945e-03;r[49]=-4.7129500e-03;r[50]=-2.5483556e-05; /*Saturne*/
r[21]=1.9916762e+01;r[22]=2.3700466e+00;r[23]=-2.4922728e-01;r[51]=-4.9354675e-04;r[52]=3.7222065e-03;r[53]=2.0227673e-05; /*Uranus*/
r[24]=2.6481558e+01;r[25]=-1.4076556e+01;r[26]=-3.2040642e-01;r[54]=1.4527105e-03;r[55]=2.7901455e-03;r[56]=-9.1342324e-05; /*Neptune*/
r[27]=4.9371124e+00;r[28]=-3.1890424e+01;r[29]=1.9843679e+00;r[57]=3.1711953e-03;r[58]=-1.4100225e-04;r[59]=-9.0807325e-04; /*Pluton*/

	/*Perihelie:Conditions Initiales&Initialisation*/
	double w_old_old[11],w_old[11],w[11];/*w_old_old:r(t-dt);w_old:r(t);w:r(t+dt);r par rapport au soleil*/
	for(j=30;j<60;j=j+3){
		for(i=0;i<10;i++){
			k=i*3;
			w[i+1]=sqrt(((r[j-30]-r[k])*(r[j-30]-r[k]))+((r[j-29]-r[k+1])*(r[j-29]-r[k+1]))+((r[j-28]-r[k+2])*(r[j-28]-r[k+2])));
		}
	}
	for(i=0;i<11;i++){
		w_old[i]=0;
	}
	w[0]=tmin;
	for(i=1;i<11;i++){
		w[i]=0/*TS*/;
	}

	/*Evolution temporelle*/
	for(t=tmin;t<tmax;t=t+dt){
		/*Exportation des données:temps*/
		fprintf(fich0,"%lf ",t);
		fprintf(fich3,"%lf ",t);
		/*Exportation des données:positions*/
		for(i=0;i<30;i++){
			fprintf(fich0,"%le ",r[i]);
		}
		fprintf(fich0,"\n");

		/*Détermination des périhélies*/
		for(i=0;i<11;i++){
			w_old_old[i]=w_old[i];
			w_old[i]=w[i];
		}
		w[0]=t;
		f(r,dr,w);		/*dr a partir de r & creation de w[]*/
		euler(r,dr,dt);	/*r(t)->r(t+dt)*/ 

		for (i=1;i<11;i++){
			if((w_old[i]<w_old_old[i])&&(w[i]>w_old[i])){	/*?si minimum local*/
				fprintf(fich3, "%le ", w[i]);				/*exportation du minimum local*/
			}
			else{
				fprintf(fich3,"_ ");
			}
		}
		fprintf(fich3,"\n");

	}/*fin de la boucle sur le temps*/

	/*fermeture des fichiers*/
	fclose(fich0);
	fclose(fich3);
	return 0;
}

