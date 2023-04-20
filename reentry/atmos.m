%%%Résolution - Entrée en atmosphère terrestre%%%

clear all
close all 

rE=6378e3;    %rayon terrestre

%% Résolution de l'équation différentielle

% for ii=6500e3:0.1e3:6502e3    %%%Boucle
%close all                      %%%Boucle

x0=0e3;                         %Position initiale selon x 
y0=6458e3;                      %Position initiale selon y
r0=sqrt((x0^2)+(y0^2));         %Distance du centre de la terre initiale
z0=r0-rE;                       %Altitude initiale
ux=x0/r0;
theta_x=acos(ux);               %theta initiale
uy=x0/r0;
theta_y=acos(uy);               %theta initiale
    
TT=1000;                                                 %Temps maximale pour la résolution
[T,Y] = ode45(@atmo,[0 TT],[5000 0.2 r0 theta_x]);     %Résolution de l'équation différentielle

z=Y(:,3) - rE;                                          %Altitude

%conditions physiques
% Y(Y(:,3)<6378e3)=6378e3;
% z(z(:,1)<0)=0;

%% Partie graphique - Coordonnées cartésiens

%%%modélisation de la terre

%centre de la terre
xc=0;                       
yc=0;                       

%surface de la terre
theta = linspace(0,2*pi);
x = rE*cos(theta) + xc;
y = rE*sin(theta) + yc;

%trajectoire de la navette spatiale
x2 = Y(:,3).*cos(Y(:,4));
y2 = Y(:,3).*sin(Y(:,4));

%graphique
scrsz = get(0,'ScreenSize');

figure('Position',[scrsz(3)/50 scrsz(4)/4 scrsz(3)/2.2 scrsz(4)/2.2])
subplot(221)
plot(T,Y(:,1))
title('Vitesse')

subplot(222)
plot(T,Y(:,2))
title('Gamma')

subplot(223)
plot(T,Y(:,3))
title('Rayon')

subplot(224)
plot(T,Y(:,4))
title('Theta')

figure('Position',[scrsz(3)/2 scrsz(4)/4 scrsz(3)/2.2 scrsz(4)/2.2])
subplot(121)
plot(T,z)
title('altitude')
axis([0 TT 0 2.5*z0])

subplot(122)
plot(x,y,'b-')      %terre
hold on
plot(x2,y2,'r')     %trajectoire
% title(ii)                 %%%Boucle
axis equal
axis([-10e6 10e6 -10e6 10e6])
% pause                     %%%Boucle
% end                       %%%Boucle

%%
%Température
% c0=sqrt(287.05*1.4*293); %vitesse du son dans l'air
% M= Y(:,1)/c0;   %nombre de Mach
% T1=293;     %temperature de l'air initiale
% M2=M.^2;
% T2=T1*(((1+0.2.*M2).*(7*M2-1))/(7.2*M2)); %temperature extérieur au fil du temps
% Tc=293;     %température initiale de la navette=température de l'air(approximation)
rho0=1.2;                       %densité de l'air à z=0
rho=rho0*exp(-(0.1385e-3).*z);   %variation de la densité en fonction de z
% A=400;                          %surface effective pour la portance et la traînée
% m=70e3;
% dQ=(rho).^0.5*A*(Tc-T2(:,1))
% 
% for tt=1:nnz(T2(:,1))
%     TC(1)=Tc
%     
%     TC(tt)=Tc(tt)+ dQ/(m)
% end
% 
% figure
% plot (T,TC)

%H
G=6.67384e-11;                  %constante de gravitation
ME=5.972e24;                    %masse de la terre
k=G*ME;
vc=sqrt(k/rE);

H= (1/1200).*(rho/rho0).*(Y(:,1)./vc).^3;
figure
plot (T,H)
hold on
plot (T,2.3e-5,'r')
hold off




%% Graphique - Coordonnées polaires
% figure
% subplot(121)
% plot(T,z)
% title('altitude')
% 
% angle = 0:0.01:2*pi;
% subplot(122)
% polar(angle,rE*sqrt((cos(angle).^2+sin(angle).^2)),'b')   %Terre
% hold on
% polar(Y(:,4),Y(:,3).*sqrt((cos(Y(:,4)).^2+sin(Y(:,4)).^2)),'r')   %Trajectoire