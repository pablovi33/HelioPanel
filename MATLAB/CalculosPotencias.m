clc

%Inicio de la tabla

%################### 3 paneles fijos################

%ejeX = linspace(40,140,11)
%6.7 horas de 40 a 140 grados
ejeX = linspace(0,6.7,11)

V_P_IZQ_fijo_D = importdata("V_P_IZQ_fijo.txt")
I_P_IZQ_fijo_D = importdata("I_P_IZQ_fijo.txt")
I_P_IZQ_fijo_C = (10.^(-3))*I_P_IZQ_fijo_D

%Datos parseados
V_P_IZQ_fijo=V_P_IZQ_fijo_D.'
I_P_IZQ_fijo=I_P_IZQ_fijo_C.'

V_P_CEN_fijo_D = importdata("V_P_CEN_fijo.txt")
I_P_CEN_fijo_D = importdata("I_P_CEN_fijo.txt")
I_P_CEN_fijo_C = (10.^(-3))*I_P_CEN_fijo_D

%Datos parseados
V_P_CEN_fijo=V_P_CEN_fijo_D.'
I_P_CEN_fijo=I_P_CEN_fijo_C.'

V_P_DER_fijo_D = importdata("V_P_DER_fijo.txt")
I_P_DER_fijo_D = importdata("I_P_DER_fijo.txt")
I_P_DER_fijo_C = (10.^(-3))*I_P_DER_fijo_D

%Datos parseados
V_P_DER_fijo=V_P_DER_fijo_D.'
I_P_DER_fijo=I_P_DER_fijo_C.'

polV_P_IZQ_fijo = polyfit(ejeX,V_P_IZQ_fijo,5)
polI_P_IZQ_fijo = polyfit(ejeX,I_P_IZQ_fijo,5)

%inicio IZQ

fV_P_IZQ_fijo = polyval(polV_P_IZQ_fijo,ejeX);
fI_P_IZQ_fijo = polyval(polI_P_IZQ_fijo,ejeX);
%fP=fV*fI;
fPot_P_IZQ_fijo = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_IZQ_fijo(h)=fV_P_IZQ_fijo(h)*fI_P_IZQ_fijo(h)
end



a = ejeX(1);%elecccion de primer elemento
b = ejeX(11);%eleccion de ultimo elemento

polPot_P_IZQ_fijo= polyfit(ejeX,fPot_P_IZQ_fijo,5)

%inicio CEN

polV_P_CEN_fijo = polyfit(ejeX,V_P_CEN_fijo,5)
polI_P_CEN_fijo = polyfit(ejeX,I_P_CEN_fijo,5)

fV_P_CEN_fijo = polyval(polV_P_CEN_fijo,ejeX);
fI_P_CEN_fijo = polyval(polI_P_CEN_fijo,ejeX);
%fP=fV*fI;
fPot_P_CEN_fijo = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_CEN_fijo(h)=fV_P_CEN_fijo(h)*fI_P_CEN_fijo(h)
end

polPot_P_CEN_fijo= polyfit(ejeX,fPot_P_CEN_fijo,5)

%inicio DER

polV_P_DER_fijo = polyfit(ejeX,V_P_DER_fijo,5)
polI_P_DER_fijo = polyfit(ejeX,I_P_DER_fijo,5)

fV_P_DER_fijo = polyval(polV_P_DER_fijo,ejeX);
fI_P_DER_fijo = polyval(polI_P_DER_fijo,ejeX);
%fP=fV*fI;
fPot_P_DER_fijo = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_DER_fijo(h)=fV_P_DER_fijo(h)*fI_P_DER_fijo(h)
end

polPot_P_DER_fijo= polyfit(ejeX,fPot_P_DER_fijo,5)

%FINE

Pot_P_IZQ_fijo=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_IZQ_fijo(h)=V_P_IZQ_fijo(h)*I_P_IZQ_fijo(h);
end

Pot_P_CEN_fijo=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_CEN_fijo(h)=V_P_CEN_fijo(h)*I_P_CEN_fijo(h);
end

Pot_P_DER_fijo=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_DER_fijo(h)=V_P_DER_fijo(h)*I_P_DER_fijo(h);
end

%#####################Seguidor 1######################

V_P_IZQ_seg_1_D = importdata("V_P_IZQ_seg_1.txt")
I_P_IZQ_seg_1_D = importdata("I_P_IZQ_seg_1.txt")
I_P_IZQ_seg_1_C = (10.^(-3))*I_P_IZQ_seg_1_D

%Datos parseados
V_P_IZQ_seg_1 = V_P_IZQ_seg_1_D.'
I_P_IZQ_seg_1 = I_P_IZQ_seg_1_C.'

V_P_CEN_seg_1_D = importdata("V_P_CEN_seg_1.txt")
I_P_CEN_seg_1_D = importdata("I_P_CEN_seg_1.txt")
I_P_CEN_seg_1_C = (10.^(-3))*I_P_CEN_seg_1_D

%Datos parseados
V_P_CEN_seg_1 = V_P_CEN_seg_1_D.'
I_P_CEN_seg_1 = I_P_CEN_seg_1_C.'

V_P_DER_seg_1_D = importdata("V_P_DER_seg_1.txt")
I_P_DER_seg_1_D = importdata("I_P_DER_seg_1.txt")
I_P_DER_seg_1_C = (10.^(-3))*I_P_DER_seg_1_D

%Datos parseados
V_P_DER_seg_1 = V_P_DER_seg_1_D.'
I_P_DER_seg_1 = I_P_DER_seg_1_C.'

polV_P_IZQ_seg_1 = polyfit(ejeX,V_P_IZQ_seg_1,5)
polI_P_IZQ_seg_1 = polyfit(ejeX,I_P_IZQ_seg_1,5)

%inicio IZQ

fV_P_IZQ_seg_1 = polyval(polV_P_IZQ_seg_1,ejeX);
fI_P_IZQ_seg_1 = polyval(polI_P_IZQ_seg_1,ejeX);
%fP=fV*fI;
fPot_P_IZQ_seg_1 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_IZQ_seg_1(h)=fV_P_IZQ_seg_1(h)*fI_P_IZQ_seg_1(h)
end

polPot_P_IZQ_seg_1= polyfit(ejeX,fPot_P_IZQ_seg_1,5)

%inicio CEN

polV_P_CEN_seg_1= polyfit(ejeX,V_P_CEN_seg_1,5)
polI_P_CEN_seg_1 = polyfit(ejeX,I_P_CEN_seg_1,5)

fV_P_CEN_seg_1 = polyval(polV_P_CEN_seg_1,ejeX);
fI_P_CEN_seg_1 = polyval(polI_P_CEN_seg_1,ejeX);
%fP=fV*fI;
fPot_P_CEN_seg_1 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_CEN_seg_1(h)=fV_P_CEN_seg_1(h)*fI_P_CEN_seg_1(h)
end

polPot_P_CEN_seg_1= polyfit(ejeX,fPot_P_CEN_seg_1,5)

%inicio DER

polV_P_DER_seg_1 = polyfit(ejeX,V_P_DER_seg_1,5)
polI_P_DER_seg_1 = polyfit(ejeX,I_P_DER_seg_1,5)

fV_P_DER_seg_1 = polyval(polV_P_DER_seg_1,ejeX);
fI_P_DER_seg_1 = polyval(polI_P_DER_seg_1,ejeX);
%fP=fV*fI;
fPot_P_DER_seg_1 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_DER_seg_1(h)=fV_P_DER_seg_1(h)*fI_P_DER_seg_1(h)
end

polPot_P_DER_seg_1= polyfit(ejeX,fPot_P_DER_seg_1,5)

%FINE

Pot_P_IZQ_seg_1=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_IZQ_seg_1(h)=V_P_IZQ_seg_1(h)*I_P_IZQ_seg_1(h)
end

Pot_P_CEN_seg_1=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_CEN_seg_1(h)=V_P_CEN_seg_1(h)*I_P_CEN_seg_1(h)
end

Pot_P_DER_seg_1=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_DER_seg_1(h)=V_P_DER_seg_1(h)*I_P_DER_seg_1(h)
end

%#################seguidor 2########################

V_P_IZQ_seg_2_D = importdata("V_P_IZQ_seg_2.txt")
I_P_IZQ_seg_2_D = importdata("I_P_IZQ_seg_2.txt")
I_P_IZQ_seg_2_C = (10.^(-3))*I_P_IZQ_seg_2_D

%Datos parseados
V_P_IZQ_seg_2 = V_P_IZQ_seg_2_D.'
I_P_IZQ_seg_2 = I_P_IZQ_seg_2_C.'

V_P_CEN_seg_2_D = importdata("V_P_CEN_seg_2.txt")
I_P_CEN_seg_2_D = importdata("I_P_CEN_seg_2.txt")
I_P_CEN_seg_2_C = (10.^(-3))*I_P_CEN_seg_2_D

%Datos parseados
V_P_CEN_seg_2 = V_P_CEN_seg_2_D.'
I_P_CEN_seg_2 = I_P_CEN_seg_2_C.'

V_P_DER_seg_2_D = importdata("V_P_DER_seg_2.txt")
I_P_DER_seg_2_D = importdata("I_P_DER_seg_2.txt")
I_P_DER_seg_2_C = (10.^(-3))*I_P_DER_seg_2_D

%Datos parseados
V_P_DER_seg_2 = V_P_DER_seg_2_D.'
I_P_DER_seg_2 = I_P_DER_seg_2_C.'

polV_P_IZQ_seg_2 = polyfit(ejeX,V_P_IZQ_seg_2,5)
polI_P_IZQ_seg_2 = polyfit(ejeX,I_P_IZQ_seg_2,5)

%inicio IZQ

fV_P_IZQ_seg_2 = polyval(polV_P_IZQ_seg_2,ejeX);
fI_P_IZQ_seg_2 = polyval(polI_P_IZQ_seg_2,ejeX);
%fP=fV*fI;
fPot_P_IZQ_seg_2 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_IZQ_seg_2(h)=fV_P_IZQ_seg_2(h)*fI_P_IZQ_seg_2(h)
end

polPot_P_IZQ_seg_2= polyfit(ejeX,fPot_P_IZQ_seg_2,5)

%inicio CEN

polV_P_CEN_seg_2= polyfit(ejeX,V_P_CEN_seg_2,5)
polI_P_CEN_seg_2 = polyfit(ejeX,I_P_CEN_seg_2,5)

fV_P_CEN_seg_2 = polyval(polV_P_CEN_seg_2,ejeX);
fI_P_CEN_seg_2 = polyval(polI_P_CEN_seg_2,ejeX);
%fP=fV*fI;
fPot_P_CEN_seg_2 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_CEN_seg_2(h)=fV_P_CEN_seg_2(h)*fI_P_CEN_seg_2(h)
end

polPot_P_CEN_seg_2= polyfit(ejeX,fPot_P_CEN_seg_2,5)

%inicio DER

polV_P_DER_seg_2 = polyfit(ejeX,V_P_DER_seg_2,5)
polI_P_DER_seg_2 = polyfit(ejeX,I_P_DER_seg_2,5)

fV_P_DER_seg_2 = polyval(polV_P_DER_seg_2,ejeX);
fI_P_DER_seg_2 = polyval(polI_P_DER_seg_2,ejeX);
%fP=fV*fI;
fPot_P_DER_seg_2 = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_DER_seg_2(h)=fV_P_DER_seg_2(h)*fI_P_DER_seg_2(h)
end

polPot_P_DER_seg_2= polyfit(ejeX,fPot_P_DER_seg_2,5)

%FINE

Pot_P_IZQ_seg_2=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_IZQ_seg_2(h)=V_P_IZQ_seg_2(h)*I_P_IZQ_seg_2(h)
end

Pot_P_CEN_seg_2=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_CEN_seg_2(h)=V_P_CEN_seg_2(h)*I_P_CEN_seg_2(h)
end

Pot_P_DER_seg_2=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_DER_seg_2(h)=V_P_DER_seg_2(h)*I_P_DER_seg_2(h)
end

%##############seguidor 15 grados######################


V_P_IZQ_seg_15g_D = importdata("V_P_IZQ_seg_15g.txt")
I_P_IZQ_seg_15g_D = importdata("I_P_IZQ_seg_15g.txt")
I_P_IZQ_seg_15g_C = (10.^(-3))*I_P_IZQ_seg_15g_D

%Datos parseados
V_P_IZQ_seg_15g = V_P_IZQ_seg_15g_D.'
I_P_IZQ_seg_15g = I_P_IZQ_seg_15g_C.'

V_P_CEN_seg_15g_D = importdata("V_P_CEN_seg_15g.txt")
I_P_CEN_seg_15g_D = importdata("I_P_CEN_seg_15g.txt")
I_P_CEN_seg_15g_C = (10.^(-3))*I_P_CEN_seg_15g_D

%Datos parseados
V_P_CEN_seg_15g = V_P_CEN_seg_15g_D.'
I_P_CEN_seg_15g = I_P_CEN_seg_15g_C.'

V_P_DER_seg_15g_D = importdata("V_P_DER_seg_15g.txt")
I_P_DER_seg_15g_D = importdata("I_P_DER_seg_15g.txt")
I_P_DER_seg_15g_C = (10.^(-3))*I_P_DER_seg_15g_D

%Datos parseados
V_P_DER_seg_15g = V_P_DER_seg_15g_D.'
I_P_DER_seg_15g = I_P_DER_seg_15g_C.'

polV_P_IZQ_seg_15g = polyfit(ejeX,V_P_IZQ_seg_15g,5)
polI_P_IZQ_seg_15g = polyfit(ejeX,I_P_IZQ_seg_15g,5)

%inicio IZQ

fV_P_IZQ_seg_15g = polyval(polV_P_IZQ_seg_15g,ejeX);
fI_P_IZQ_seg_15g = polyval(polI_P_IZQ_seg_15g,ejeX);
%fP=fV*fI;
fPot_P_IZQ_seg_15g = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_IZQ_seg_15g(h)=fV_P_IZQ_seg_15g(h)*fI_P_IZQ_seg_15g(h)
end

polPot_P_IZQ_seg_15g= polyfit(ejeX,fPot_P_IZQ_seg_15g,5)

%inicio CEN

polV_P_CEN_seg_15g = polyfit(ejeX,V_P_CEN_seg_15g,5)
polI_P_CEN_seg_15g = polyfit(ejeX,I_P_CEN_seg_15g,5)

fV_P_CEN_seg_15g = polyval(polV_P_CEN_seg_15g,ejeX);
fI_P_CEN_seg_15g= polyval(polI_P_CEN_seg_15g,ejeX);
%fP=fV*fI;
fPot_P_CEN_seg_15g = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_CEN_seg_15g(h)=fV_P_CEN_seg_15g(h)*fI_P_CEN_seg_15g(h)
end

polPot_P_CEN_seg_15g= polyfit(ejeX,fPot_P_CEN_seg_15g,5)

%inicio DER

polV_P_DER_seg_15g = polyfit(ejeX,V_P_DER_seg_15g,5)
polI_P_DER_seg_15g = polyfit(ejeX,I_P_DER_seg_15g,5)

fV_P_DER_seg_15g = polyval(polV_P_DER_seg_15g,ejeX);
fI_P_DER_seg_15g = polyval(polI_P_DER_seg_15g,ejeX);
%fP=fV*fI;
fPot_P_DER_seg_15g = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_DER_seg_15g(h)=fV_P_DER_seg_15g(h)*fI_P_DER_seg_15g(h)
end

polPot_P_DER_seg_15g= polyfit(ejeX,fPot_P_DER_seg_15g,5)

%FINE

Pot_P_IZQ_seg_15g=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_IZQ_seg_15g(h)=V_P_IZQ_seg_15g(h)*I_P_IZQ_seg_15g(h)
end

Pot_P_CEN_seg_15g=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_CEN_seg_15g(h)=V_P_CEN_seg_15g(h)*I_P_CEN_seg_15g(h)
end

Pot_P_DER_seg_15g=[0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   Pot_P_DER_seg_15g(h)=V_P_DER_seg_15g(h)*I_P_DER_seg_15g(h)
end

V_P_CEN_fijo_30g_D = importdata("V_P_CEN_fijo_30_grados.txt")
I_P_CEN_fijo_30g_D = importdata("I_P_CEN_fijo_30_grados.txt")
I_P_CEN_fijo_30g_C=(10.^(-3))*I_P_CEN_fijo_30g_D %cnversion mA

%Datos parseados
V_P_CEN_fijo_30g= V_P_CEN_fijo_30g_D.'
I_P_CEN_fijo_30g= I_P_CEN_fijo_30g_C.'




polV_P_CEN_fijo_30g = polyfit(ejeX,V_P_CEN_fijo_30g,5)
polI_P_CEN_fijo_30g = polyfit(ejeX,I_P_CEN_fijo_30g,5)

fV_P_CEN_fijo_30g = polyval(polV_P_CEN_fijo_30g,ejeX);
fI_P_CEN_fijo_30g = polyval(polI_P_CEN_fijo_30g,ejeX);
%fP=fV*fI;
fPot_P_CEN_fijo_30g = [0,0,0,0,0,0,0,0,0,0,0];
for h = 1:11
   fPot_P_CEN_fijo_30g(h)=fV_P_CEN_fijo_30g(h)*fI_P_CEN_fijo_30g(h)
end

polPot_P_CEN_fijo_30g = polyfit(ejeX,fPot_P_CEN_fijo_30g,5)

%pruebas Izquierda

figure

hold on

plot(ejeX,fPot_P_IZQ_fijo,'+')
%plot(ejeX,fPot_P_IZQ_seg_1,'--')
plot(ejeX,fPot_P_IZQ_seg_2,'-')
plot(ejeX,fPot_P_IZQ_seg_15g,'--')

hold off

legend('fijo','seguidor','trayectoria 15°')
title('Panel Izquierda')

%pruebas Centro

figure

hold on

%plot(ejeX,fV_P_CEN_fijo_30g,'+')
%plot(ejeX,fI_P_CEN_fijo_30g,'r--')
plot(ejeX,fPot_P_CEN_fijo,'+')
plot(ejeX,fPot_P_CEN_fijo_30g,'o')
%plot(ejeX,fPot_P_CEN_seg_1,'--')
plot(ejeX,fPot_P_CEN_seg_2,'-')
plot(ejeX,fPot_P_CEN_seg_15g,'--')


hold off

%legend('sin(x/2)','2016')

legend('fijo','fijo 30°','seguidor','trayectoria 15°')
title('Panel Central')

%polPot_P_DER_fijo= polyfit(ejeX,fPot_P_DER_fijo,5)

%pruebas Derecha

figure

hold on

plot(ejeX,fPot_P_DER_fijo,'+')
%plot(ejeX,fPot_P_DER_seg_1,'--')
plot(ejeX,fPot_P_DER_seg_2,'-')
plot(ejeX,fPot_P_DER_seg_15g,'--')

hold off


legend('fijo','seguidor','trayectoria 15°')
title('Panel Derecha')

%q = polyint(pV)

%######Calculo De Integrales######

q_P_IZQ_fijo = polyint(polPot_P_IZQ_fijo)
q_P_IZQ_fijo_seg_2 = polyint(polPot_P_IZQ_seg_2)
q_P_IZQ_fijo_seg_15g = polyint(polPot_P_IZQ_seg_15g)

q_P_CEN_fijo_30g = polyint(polPot_P_CEN_fijo_30g)
q_P_CEN_fijo = polyint(polPot_P_CEN_fijo)
q_P_CEN_seg_2 = polyint(polPot_P_CEN_seg_2)
q_P_CEN_seg_15g = polyint(polPot_P_CEN_seg_15g)

q_P_DER_fijo = polyint(polPot_P_DER_fijo)
q_P_DER_fijo_seg_2 = polyint(polPot_P_DER_seg_2)
q_P_DER_fijo_seg_15g = polyint(polPot_P_DER_seg_15g)


Whr_P_IZQ_fijo = diff(polyval(q_P_IZQ_fijo,[a b]))
Whr_P_IZQ_seg_2 = diff(polyval(q_P_IZQ_fijo_seg_2,[a b]))
Whr_P_IZQ_seg_15g = diff(polyval(q_P_IZQ_fijo_seg_15g,[a b]))

Whr_P_CEN_fijo_30g = diff(polyval(q_P_CEN_fijo_30g,[a b]))
Whr_P_CEN_fijo = diff(polyval(q_P_CEN_fijo,[a b]))
Whr_P_CEN_seg_2 = diff(polyval(q_P_CEN_seg_2,[a b]))
Whr_P_CEN_seg_15g = diff(polyval(q_P_CEN_seg_15g,[a b]))

Whr_P_DER_fijo = diff(polyval(q_P_DER_fijo,[a b]))
Whr_P_DER_seg_2 = diff(polyval(q_P_DER_fijo_seg_2,[a b]))
Whr_P_DER_seg_15g = diff(polyval(q_P_DER_fijo_seg_15g,[a b]))



