/*Programme:2corps-Soleil_Terre(euler)*/
#include <stdio.h>
#include <math.h>

/*Systemes d'equations differentielles;dr[] à partir de r[]*/
double f(double r[],double dr[]){
	double G=2.959122e-4,Ms=1,Mt=3.0032e-6,TS,TS2;
	int i;

	/*Distance Terre-Soleil:r*/
	TS = (((r[0]-r[3])*(r[0]-r[3]))+((r[1]-r[4])*(r[1]-r[4]))+((r[2]-r[5])*(r[2]-r[5])));	/* r² */
	TS2= TS*sqrt(TS);																		/* r³ */

	/*dr de r;accélérations et vitesses à t*/
	for(i=0;i<6;i++){
		dr[i]=r[i+6];						/* vitesses */
	}
	for(i=6;i<9;i++){
		dr[i]=G*(Mt/TS2)*(r[i-3]-r[i-6]);	/* accelerations:Soleil */
	}
	for(i=9;i<12;i++){
		dr[i]=-G*(Ms/TS2)*(r[i-6]-r[i-9]);	/* accelerations:Terre */
	}
return sqrt(TS);	/* r */
}/*fin:f*/

/*Resolution d'equation differentielle:méthode d'Euler*/
void euler(double r[],double dr[],double dt){
	int i;
	for(i=0;i<12;i++){
		r[i]=r[i]+dt*dr[i];	/*r(t+dt)=r(t)+k1*/
	}
}/*fin:euler*/

int main()
{
	FILE*fich0;
	fich0=fopen("euler2.txt","w");		/*Positions*/
	FILE*fich1;
	fich1=fopen("extra2eu.txt","w");	/*r(t),impulsions,moment cinétique total,énergie total*/
	FILE*fich3;
	fich3=fopen("pe2eu.txt","w");		/*Périhélies*/

	double t,tmin=0,tmax=10*365,dt=1;	/*en jours*/
	double r[12]/*positions(6) et vitesses(6)*/,dr[12]/*vitesses(6) et accelerations(6)*/;
	double TS/*r_i(t)*/,v[7]/*vs vt ps pt Ltot Etot ptot*/;
	double G=2.959122e-4,Ms=1,Mt=3.0032e-6;
	int i;

	/*Conditions initiales*/
		/*Positions(x,y,z)*/
	r[0] =-1.6132380e-3;	r[1] =-2.3674938e-3;	r[2] =-3.4999903e-5;	/*Soleil*/
	r[3] =6.8900355e-1;		r[4] =7.0799513e-1;		r[5] =-5.4762805e-5;	/*Terre*/
		/*Vitesses(vx,vy,vz)*/
	r[6] =6.0453208e-6;		r[7] =-1.8980631e-6;	r[8] =-1.3060634e-7;	/*Soleil*/
	r[9] =-1.2606830e-2;	r[10]=1.1932472e-2;		r[11]=-5.3326343e-7;	/*Terre*/

	/*Perihelie:Conditions Initiales&Initialisation*/
	double w_old_old[2],w_old[2],w[2];	/*w_old_old:r(t-dt);w_old:r(t);w:r(t+dt)*/
	TS=sqrt((((r[0]-r[3])*(r[0]-r[3]))+((r[1]-r[4])*(r[1]-r[4]))+((r[2]-r[5])*(r[2]-r[5]))));	/* r */
	for(i=0;i<2;i++){
		w_old[i]=0;
	}
	w[0]=tmin;
	w[1]=TS;

	/*Evolution temporelle*/
	for(t=tmin;t<tmax;t=t+dt){
		/*Exportation des données:temps*/
		fprintf(fich0,"%lf ",t);
		fprintf(fich1,"%lf ",t);
		/*Exportation des données:positions*/
		for(i=0;i<6;i++){
			fprintf(fich0,"%le ",r[i]);
		}
		fprintf(fich0,"\n");

		/*autres calculs:extra*/
		TS=f(r,dr);	/*TS:distance Terre-Soleil et création de dr[](t+dt)*/
		v[0]=sqrt(r[6]*r[6]+r[7]*r[7]+r[8]*r[8]);/*vitesse du soleil:sqrt(vs_x²+vs_y²+vs_z²)*/
		v[1]=sqrt(r[9]*r[9]+r[10]*r[10]+r[11]*r[11]);/*vitesse de la terre:sqrt(vt_x²+vt_y²+vt_z²)*/
		v[2]=Ms*v[0];/*impulsion soleil:Ms*vs*/
		v[3]=Mt*v[1];/*impulsion terre:Mt*vt*/
		v[4]=sqrt((r[1]*r[8]-r[2]*r[7])*(r[1]*r[8]-r[2]*r[7])+(r[0]*r[7]-r[1]*r[6])*(r[0]*r[7]-r[1]*r[6])+(r[6]*r[2]-r[0]*r[8])*(r[6]*r[2]-r[0]*r[8])+(r[4]*r[11]-r[8]*r[10])*(r[4]*r[11]-r[8]*r[10])+(r[6]*r[10]-r[7]*r[9])*(r[6]*r[10]-r[7]*r[9])+(r[9]*r[8]-r[6]*r[11])*(r[9]*r[8]-r[6]*r[11]));/*L_tot*/
		v[5]=0.5*Ms*v[0]*v[0]+0.5*Mt*v[1]*v[1]+G*Ms*Mt/(r[0]*r[0]+r[1]*r[1]+r[2]*r[2])-G*Ms*Mt/(r[6]*r[6]+r[7]*r[7]+r[8]*r[8]);	/*E_tot*/
		v[6]=v[2]+v[3];/*somme des impulsions*/
  
		/*Exportation des données:extras*/
		fprintf(fich1,"%le ",TS);
		for(i=0;i<7;i++){
			fprintf(fich1,"%le ",v[i]);
		}
		fprintf(fich1,"\n");

		/*r(t)->r(t+dt)*/ 
		euler(r,dr,dt);
	
		/*Détermination des périhélies*/
		for(i=0;i<2;i++){
			w_old_old[i]=w_old[i];
			w_old[i]=w[i];
		}
		w[0]=t;
		w[1]=TS;
		if((w_old[1]<w_old_old[1])&&(w[1]>w_old[1])){	/*?si minimum local*/
			fprintf(fich3,"%le %le\n",t,TS);/*exportation du minimum local*/
		}

	}/*fin de la boucle sur le temps*/

	/*fermeture des fichiers*/
	fclose(fich0);
	fclose(fich1);
	fclose(fich3);
	return 0;
}

