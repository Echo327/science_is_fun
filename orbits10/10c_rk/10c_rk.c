/*Programme:10corps(Runge-Kutta)*/
#include <stdio.h>
#include <math.h>

/*Systemes d'equations differentielles;dr[] à partir de r[]*/
void f(double z[],double dz[],double w[],double wx[],double wy[],double wz[]){
	double G=2.959122e-4,M[10],d[10],d2[10];
	int i,j,k;

	/*Masses des planètes*/
	M[0]=1;/*Soleil*/
	M[1]=1.6600e-7;/*Mercure*/  M[2]=2.4476e-6;/*Venus*/    M[3]=3.0031e-6;/*Terre*/
	M[4]=3.2268e-7;/*Mars*/     M[5]=9.5425e-4;/*Jupiter*/  M[6]=2.8572e-4;/*Saturne*/
	M[7]=4.3643e-5;/*Uranus*/   M[8]=5.1486e-5;/*Neptune*/  M[9]=6.6060e-9;/*Pluton*/

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
			d[j]=((z[i-30]-z[k])*(z[i-30]-z[k]))+((z[i-29]-z[k+1])*(z[i-29]-z[k+1]))+((z[i-28]-z[k+2])*(z[i-28]-z[k+2]));
			d2[j]=d[j]*sqrt(d[j]);
			if(d2[j]!=0){	/*somme des contributions d'accelerations*/
				dz[i]=dz[i]- G*(M[j]/d2[j])*(z[i-30]-z[k]);
				dz[i+1]=dz[i+1]- G*(M[j]/d2[j])*(z[i-29]-z[k+1]);
				dz[i+2]=dz[i+2]- G*(M[j]/d2[j])*(z[i-28]-z[k+2]);
			}
			if(i==30){
				w[j+1]=sqrt(d[j]);			/*distance du planète j par rapport au soleil*/
				wx[j+1]=z[i-30]-z[k];		/*distance selon x du planète j par rapport au soleil*/
				wy[j+1]=z[i-29]-z[k+1];		/*distance selon y du planète j par rapport au soleil*/
				wz[j+1]=z[i-28]-z[k+2];		/*distance selon z du planète j par rapport au soleil*/
			}
		}
	}
}/*fin:f*/

/*Resolution d'equation differentielle*/
void rk(double r[],double dr[],double dt){
	double k1[60],k2[60],k3[60],k4[60],d1[60]/*r[] intermédiaire*/,d2[60]/*dr intermédiaire*/,w1[11]/*vecteur "fantome"*/;
	int i;
	for(i=0;i<11;i++){
	w1[i]=0;
	}
	for(i=0;i<60;i++){
		k1[i]=dt*dr[i];			/*k1*/
		d1[i]=r[i]+0.5*k1[i];	/*r+0.5k1*/
	}
	f(d1,d2,w1,w1,w1,w1);		/*dr de r+k1*/

	for(i=0;i<60;i++){
		k2[i]=dt*d2[i];			/*k2*/
		d1[i]=r[i]+0.5*k2[i];	/*r+0.5k2*/
	}
	f(d1,d2,w1,w1,w1,w1);		/*dr de r+k2*/

	for(i=0;i<60;i++){
		k3[i]=dt*d2[i];			/*k3*/
		d1[i]=r[i]+k3[i];		/*r+k3*/
	}
	f(d1,d2,w1,w1,w1,w1);		/*dr de r+k3*/

	for(i=0;i<60;i++){
		k4[i]=dt*d2[i];			/*k4*/
		r[i]=r[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;	/*r(t+dt)=r(t)+1/6(k1+2k2+2k3+k4)*/
	}
}

/*delta phy*/
double calcul_angle(double w,double w0,double wx,double wy,double wz,double wx0,double wy0,double wz0){
return (acos((wx*wx0+wy*wy0+wz*wz0)/(w*w0)));
}

int main()
{
	FILE*fich0;
	fich0=fopen("rk10.txt","w");		/*positions*/
	FILE*fich3;
	fich3=fopen("pe10rk.txt","w");		/*delta phy(radians)*/

	double t,tmin=0,tmax=92000*2,dt=0.1;	/*en jours*/
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

	/*Perihelie_Conditions Initiales_initialisation*/
		/*w_old_old:r(t-dt); w_old:r(t); w:r(t+dt); r par rapport au soleil*/
		/*wx[],wy[],wz[]:distance selon x,y,z du planète j par rapport au soleil*/
	double w_old_old[11],w_old[11],w[11],wx[11],wy[11],wz[11],w0[11]/*1er minima*/,nb_w[11]/*nombres de minima*/;
	w[0]=tmin;
	wx[0]=tmin;
	wy[0]=tmin;
	wz[0]=tmin;
	w0[0]=0;
	nb_w[0]=0;
	for(j=30;j<60;j=j+3){
		for(i=0;i<10;i++){
			k=i*3;
			w[i+1]=((r[j-30]-r[k])*(r[j-30]-r[k]))+((r[j-29]-r[k+1])*(r[j-29]-r[k+1]))+((r[j-28]-r[k+2])*(r[j-28]-r[k+2]));
			wx[i+1]=r[j-30]-r[k];
			wy[i+1]=r[j-29]-r[k+1];
			wz[i+1]=r[j-28]-r[k+2];
			nb_w[i+1]=0;
		}
	}
	for(i=0;i<11;i++){
		w_old[i]=0;
	}
	double wx0[11],wy0[11],wz0[11];	/*x,y,x des 1er minima:initialisation*/
	wx0[0]=0;
	wy0[0]=0;
	wz0[0]=0;

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

	f(r,dr,w,wx,wy,wz);	/*dr a partir de r & creation de w[]*/
	rk(r,dr,dt);		/*r(t)->r(t+dt)*/ 

	
	for (i=1;i<11;i++){
		if ((w_old[i]<w_old_old[i])&&(w[i]>w_old[i])){
			nb_w[i]++;
			if (nb_w[i]==1){ /*1er minimum de r(t) pour planete i?*/
				wx0[i]=wx[i];
				wy0[i]=wy[i];
				wz0[i]=wz[i];
				w0[i]=w[i];		
			}
		fprintf(fich3, "%le ", calcul_angle(w[i],w0[i],wx[i],wy[i],wz[i],wx0[i],wy0[i],wz0[i]));/*Exportation:delta phy(radians)*/
		}
		else {
			fprintf(fich3, "_ ");	/*pas de valeur à ce temps,t*/
		}
	}
	fprintf(fich3, "\n");
}

fclose(fich0);
fclose(fich3);
return 0;
}

