//DESCRIPCION
/*
*
*Para obtener la lectura anlogica de las fotoresistencias
*
*Equema
*                      A
*              ________________
*             |LEC 1       LEC3|
*             |(J1)        (J3)|
*             |                |
*Lado IZQ     |                |      Lado DER
*             |                |
*             |(J2)        (J4)|
*             |LEC 0       LEC2|
*             -----------------
*                      B
* Por lo tanto:
*LEC0 es J2 es B_L (bottom left)  
*LEC1 es J1 es U_L (upper left)
*LEC2 es J4 es B_R (bottom right)
*LEC3 es J3 es U_R (upper right)
*
*  Para Panel Izquierda
*
*LEC0 es J2 es B_L (bottom left)   PIN A13
*LEC1 es J1 es U_L (upper left)    PIN A10
*LEC2 es J4 es B_R (bottom right)  PIN A12
*LEC3 es J3 es U_R (upper right)   PIN A11
*
*  Para Panel Central
*
*LEC0 es J2 es B_L (bottom left)   PIN A3
*LEC1 es J1 es U_L (upper left)    PIN A4
*LEC2 es J4 es U_R (upper right)   PIN A9
*LEC3 es J3 es B_R (bottom right)  PIN A5
*
*

*
*____________         ____________          ____________
*|Paso 0     |        |Paso 1     |         |Paso 2     |
*|Alinea Rho |   ->   |Alinea Fi  |    ->   |Detiene Fi |
*|___________|        |___________|         |___________|
*
*
*/


//variables para Panel Izquierda
        int AF0_0 = analogRead(A10);
        int AF0_1 = analogRead(A13);
        int AF0_2 = analogRead(A11);
        int AF0_3 = analogRead(A12);

//Variables para panel Derecha
        int AF1_A = analogRead(A14);
        int AF1_B = analogRead(A15);

//Variables para panel Central
        int AF2_0 = analogRead(A3);
        int AF2_1 = analogRead(A4);
        int AF2_2 = analogRead(A9);
        int AF2_3 = analogRead(A5);
 
//Panel Izquierda

//movimiento Vertical
       if(((AF0_3)>=(AF0_2))&&((AF0_1)>=(AF2_0))){
        //sentido aparentemente positivo
    
       }
       else{
          //sentido aparentemente negativo
       }

       //movimiento Horizontal
        if(((AF0_3)>=(AF0_1))&&((AF0_2)>=(AF2_0))){
           //sentido aparentemente positivo
        }
        else{
           //sentido aparentemente negativo
        }

//Panel Central

//movimiento Vertical
       if(((AF2_3)>=(AF2_2))&&((AF2_1)>=(AF2_0))){
          //sentido aparentemente positivo
       }
       else{
          //sentido aparentemente negativo
       }

       //movimiento Horizontal
        if(((AF2_3)>=(AF2_1))&&((AF2_2)>=(AF2_0))){
            //sentido aparentemente positivo
        }
        else{
           //sentido aparentemente negativo
        }

