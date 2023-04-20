%%%Equations diff�rentielles pour l'entr�e en atmosphere terrestre%%%

function dy = atmo(t,y)

dy=zeros(4,1);

rE=6378e3;                      %rayon terrestre

%train�e
z=y(3)- rE;                     %altitude
rho0=1.2;                       %densit� de l'air � z=0
rho=rho0*exp(-(0.1385e-3)*z);   %variation de la densit� en fonction de z
A=400;                          %surface effective pour la portance et la tra�n�e
CD=1;                        %coefficient de la tra�n�e
D=0.5*rho*CD*A*(y(1)^2);        %la train�e en fonction de rho(z)

%portance
CL=0;                       %coefficient de portance
L=0.5*rho*CL*A*(y(1)^2);        %la portance en fonction de rho(z)

%constante k (force de gravit�)
G=6.67384e-11;                  %constante de gravitation
ME=5.972e24;                    %masse de la terre
k=G*ME;

%masse de la navette spatiale
m=70e3;

%syst�me d'�quation diff�rentielle
dy(1) = (-D/m)-(k*(sin(y(2)))/(y(3)^2));
dy(2) = (1/y(1))*((L/m)+((y(1)^2)*(cos(y(2))/(y(3))))-(k*(cos(y(2))/(y(3)^2))));
dy(3) = y(1)*sin(y(2));
dy(4) = y(1)*(cos(y(2))/(y(3)));

%y(1) : vitesse,v de la navette
%y(2) : gamma(incidence)
%y(3) : distance r, de la navette du centre de la terre
%y(4) : theta, angle entre l'horizon et la navette

