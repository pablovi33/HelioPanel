
#include <Arduino.h>
#include <MemoryFree.h>
#include <EEPROM.h>

#include <PanelStepper.h>
#include <Wire.h>


#define PIN_LED 13    // Salida del LED
String inString;

PanelStepper mimotor;

 // int limLento=50;
 int limLento=25;
 

  //int rampa=30;
  int rampa[12]={15,30,45,60,75,90,105,120,135,150,165,180};

 int carrera[12]={20,40,60,80,100,120,140,160,180,200,220,240};
  

#define stepsPerRevolution 2000

//float toleranciaIZQhor =10;
//float toleranciaIZQver =25;


int pasoIZQ;

void AutoIZQ(float toleranciaIZQhor =60,float toleranciaIZQver =10){
          //#########################Ajuste automAtico del Panel Izquierda##############################
            //halloIZQ

    
    pasoIZQ=0;
    for(int g=0;g<10000;g++){

        int AF0_0_n = analogRead(A10);
        int AF0_1_n = analogRead(A13);
        int AF0_2_n = analogRead(A11);
        int AF0_3_n = analogRead(A12);

        int AF0_0 = map(AF0_0_n, 5, 740, 0, 1000);
        int AF0_1 = map(AF0_1_n, 11, 951, 0, 1000);
        int AF0_2 = map(AF0_2_n, 5, 840, 0, 1000);
        int AF0_3 = map(AF0_3_n, 6, 830, 0, 1000);

        int irrArribaIZQ=(AF0_0+AF0_2)/2;
        int irrAbajoIZQ=(AF0_1+AF0_3)/2;
        int irrDerechaIZQ=(AF0_2+AF0_3)/2;
        int irrIzquierdaIZQ=(AF0_0+AF0_1)/2;
        
            switch (pasoIZQ)
            {
            case 0:
            //movimiento Horizontal
                    //if(abs(AF0_1 - AF0_3) > toleranciaIZQhor){
                      //if (AF0_1 < AF0_3) {
                    if(abs(irrDerechaIZQ - irrIzquierdaIZQ) > toleranciaIZQhor){
                       if (irrDerechaIZQ < irrIzquierdaIZQ) {
               
                          //mimotor.mover(4,10,12,0); 
                          mimotor.mover(1,5,6,1);
                        }
                        else{
                          //mimotor.mover(4,10,12,1); 
                          mimotor.mover(1,5,6,0);
                        }
                    }else{
                      //nada
                      delay(10);
                      pasoIZQ=1;   
                      //break;
                    }
              break;
            case 1:
             //movimiento Vertical
                //if(abs(AF0_2-AF0_3) > toleranciaIZQver){
                  //    if (AF0_2<AF0_3) {
              if(abs(irrArribaIZQ-irrAbajoIZQ) > toleranciaIZQver){
                    if (irrArribaIZQ<irrAbajoIZQ) {

                    //sentido 
                    //mimotor.mover(8,10,12,0);  
                    mimotor.mover(2,5,6,0);    
                  }
                  else{
                      //sentido
                  //mimotor.mover(8,10,12,1);
                  mimotor.mover(2,5,6,1);       
                  }
                }else{
                  //nada
                   g=10000;//rompe ciclo for
                }
              break;
            
            default:
              break;
            }  
          }
}//fin auto IZQ

int pasoCEN=0;

void AutoCEN(float toleranciaCENhor =10,float toleranciaCENver =10){
       
          //#####################Ajuste automAtico del Panel Central#######################
    
    pasoCEN=0;
    for(int g=0;g<10000;g++){

        int AF2_0_n = analogRead(A3);
        int AF2_1_n = analogRead(A4);
        int AF2_2_n = analogRead(A9);
        int AF2_3_n = analogRead(A5);

         //Variables para panel Central
        int AF2_0 =  map(AF2_0_n, 9, 770, 0, 900);//
        int AF2_1 =  map(AF2_1_n, 12, 730, 0, 900);
        int AF2_2 =  map(AF2_2_n, 5, 900, 0, 900);
        int AF2_3 =  map(AF2_3_n, 6, 830, 0, 900);

      

            switch (pasoCEN)
            {
            case 0:
            //movimiento Horizontal
                    if(abs(AF2_1 - AF2_2) > toleranciaCENhor){
                      if (AF2_1 < AF2_2) {
                        //if(AF2_1<AF2_2){
                          //mimotor.mover(4,10,12,0); 
                          mimotor.mover(4,5,6,0);
                        }
                        else{
                          //mimotor.mover(4,10,12,1); 
                          mimotor.mover(4,5,6,1);
                        }
                    }else{
                      //nada
                      delay(10);
                      pasoCEN=1;   
                      //break;
                    }
              break;
            case 1:
             //movimiento Vertical
                if(abs(AF2_3 - AF2_2) > toleranciaCENver){
                      if (AF2_3 < AF2_2) {
                  //if(AF2_3<AF2_2){
                    //sentido 
                    //mimotor.mover(8,10,12,0);  
                    mimotor.mover(8,5,6,0);    
                  }
                  else{
                      //sentido
                  //mimotor.mover(8,10,12,1);
                  mimotor.mover(8,5,6,1);       
                  }
                }else{
                  //nada
                   g=10000;//rompe ciclo for
                }
              break;
            
            default:
              break;
            }  
          }
}//fin autoCEN

int pasoDER;

void AutoDER(float toleranciaDER =20){
  //#################Ajuste Automático Panel Derecha##########################
        pasoDER=0;
         for(int g=0;g<7000;g++){
        //Variables para panel Derecha
        int AF1_A_n = analogRead(A14);
        int AF1_B_n = analogRead(A15);

        //Variables para panel Derecha
        int AF1_A =  map(AF1_A_n, 19, 960, 0, 1000);
        int AF1_B =  map(AF1_B_n, 33, 715, 0, 1000);
       
       switch (pasoDER)
       {
       case 0:
          
          
               //movimiento Horizontal
               //movimiento Horizontal
              if(abs(AF1_A-AF1_B) > toleranciaDER){
                if(AF1_A>AF1_B){
                      //sentido aparentemente positivo
                      //mimotor.mover(16,10,12,0);
                      mimotor.mover(16,5,6,1);  
                  }
                  else{
                    //sentido aparentemente negativo
                     //mimotor.mover(16,10,12,1); 
                     mimotor.mover(16,5,6,0); 
                  }
              }else{
                pasoDER=1;
                      //nada
                   //g=5000;//rompe ciclo for
              }
           

                //fin movimiento Horizontal
        break;
        case 1:
               //movimiento vertical
              //digitalWrite(PIN_LED, LOW);
              Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
              Wire.write("q");
              delay(10);
              Wire.write("r");
                Wire.endTransmission();
              g=7000;//rompe ciclo for
        break;
       
       default:
        break;
         }
       }

}

void setup() {
  // InicializaciOn de puertos y salidas
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  
   pinMode(3,INPUT);
   
  digitalWrite(PIN_LED, LOW);

  Wire.begin();// comunicacion I2C

}


void loop() {

//ejemplo de transmision
      //Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
       //   Wire.write("l");
       // Wire.endTransmission();

        // Espera la respuesta del ESP32
        delay(100); // Asegúrate de darle suficiente tiempo al ESP32 para procesar y responder

        // Lee los datos enviados por el ESP32
       // Wire.requestFrom(0x50, 2);
       // while (Wire.available()) {
       //   int analogValue = Wire.read();
       //   Serial.print("Analog value: ");
       //   Serial.println(analogValue);
       // }

       // delay(1000); // Espera antes de enviar otro comando
          
        // codigo que se repite:
        //AF -> Arreglo de fotoresistencias
        //AF0 para panel central
        //AF1 para panel Derecha 
        //AF2 para panel Izquierda
        // lecturasAnalogicas
        

//variables para Panel Izquierda
        int AF0_0_n = analogRead(A10);
        int AF0_1_n = analogRead(A13);
        int AF0_2_n = analogRead(A11);
        int AF0_3_n = analogRead(A12);

//Variables para panel Derecha
        int AF1_A_n = analogRead(A14);
        int AF1_B_n = analogRead(A15);

//Variables para panel Central
        int AF2_0_n = analogRead(A3);
        int AF2_1_n = analogRead(A4);
        int AF2_2_n = analogRead(A9);
        int AF2_3_n = analogRead(A5);

        //MAPEO de variables

        //variables para Panel Izquierda
        //map(value, fromLow, fromHigh, toLow, toHigh)
        
        int AF0_0 = map(AF0_0_n, 5, 740, 0, 1000);
        int AF0_1 = map(AF0_1_n, 11, 951, 0, 1000);
        int AF0_2 = map(AF0_2_n, 5, 840, 0, 1000);
        int AF0_3 = map(AF0_3_n, 6, 830, 0, 1000);

//Variables para panel Derecha
        //int AF1_A =  map(AF1_A_n, 70, 1023, 0, 600);
        //int AF1_B =  map(AF1_B_n, 130, 985, 0, 600);
        int AF1_A =  map(AF1_A_n, 19, 960, 0, 1000);
        int AF1_B =  map(AF1_B_n, 33, 715, 0, 1000);


//Variables para panel Central
        int AF2_0 =  map(AF2_0_n, 9, 770, 0, 900);//
        int AF2_1 =  map(AF2_1_n, 12, 730, 0, 900);
        int AF2_2 =  map(AF2_2_n, 5, 900, 0, 900);
        int AF2_3 =  map(AF2_3_n, 6, 830, 0, 900);


        
       

        // impresion de datos en monitor serial:
int selPrint = 4;

        //Serial.println("######################################");

  switch (selPrint)
  {
  case 1:
  //PANEL IZQUIERDO
    Serial.print("AF0_0_n:");
          Serial.print(AF0_0_n);
          Serial.print("  AF0_1_n: ");
          Serial.print(AF0_1_n);
          Serial.print("  AF0_2_n: ");
          Serial.print(AF0_2_n);
          Serial.print("  AF0_3_n: ");
          Serial.println(AF0_3_n);
          break;

  case 2:
  //PANEL DERECHA
 // impresion de datos en monitor serial:
        Serial.print("AF1_A_n:");
        Serial.print(AF1_A_n);
        Serial.print("  AF1_B_n: ");
        Serial.println(AF1_B_n);
        break;

  case 3:
      //PANEL CENTRAL
        // impresion de datos en monitor serial:
        Serial.print("AF2_0_n:");
        Serial.print(AF2_0_n);
        Serial.print("  AF2_1_n: ");
        Serial.print(AF2_1_n);
        Serial.print("  AF2_2_n: ");
        Serial.print(AF2_2_n);
        Serial.print("  AF2_3_n: ");
        Serial.println(AF2_3_n);
        break;
  case 4:
  //PANEL IZQUIERDO
    Serial.print("AF0_0:");
          Serial.print(AF0_0);
          Serial.print("  AF0_1: ");
          Serial.print(AF0_1);
          Serial.print("  AF0_2: ");
          Serial.print(AF0_2);
          Serial.print("  AF0_3: ");
          Serial.println(AF0_3);
          break;

  case 5:
  //PANEL DERECHA
 // impresion de datos en monitor serial:
        Serial.print("AF1_A:");
        Serial.print(AF1_A);
        Serial.print("  AF1_B: ");
        Serial.println(AF1_B);
        break;

  case 6:
      //PANEL CENTRAL
        // impresion de datos en monitor serial:
        Serial.print("AF2_0:");
        Serial.print(AF2_0);
        Serial.print("  AF2_1: ");
        Serial.print(AF2_1);
        Serial.print("  AF2_2: ");
        Serial.print(AF2_2);
        Serial.print("  AF2_3: ");
        Serial.println(AF2_3);

    break;

  default:
    break;
  }
        


        delay(1);  // retraso de estabilidad

        


    //Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
    //Wire.write("a");
    //Wire.endTransmission();
}

// Verificacion de la conectividad entre la Mega y ESP8266
void serialEvent3() {

  while (Serial3.available()) {
    // Lectura de datos del Serial3
    char inChar = Serial3.read();
    // Salida de los datos leídos en el puerto serie
    Serial.write(inChar);
    // Buscamos si recibimos un ON o un OFF desde la Web para actuvar o no el LED de la Mega(debe estar entre corchetes [])
    inString += inChar;
    if (inChar == ']') {
      if (inString.indexOf("[ON]")>0) {
        digitalWrite(PIN_LED, HIGH);
          //mimotor.mover1(2,carrera[0],rampa,0,limLento,0);
      }
      else if (inString.indexOf("[OFF]")>0) {
        digitalWrite(PIN_LED, LOW);
      }
       else if (inString.indexOf("[R3IZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("g");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[R2IZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("h");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[R1IZQ]")>0) {
       // digitalWrite(PIN_LED, LOW);
       
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("i");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[IIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);

         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("j");
         delay(10);
         Wire.write("r");
         Wire.endTransmission();
      }
       else if (inString.indexOf("[IDER]")>0) {
        //digitalWrite(PIN_LED, LOW);

        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("k");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[R1DER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("l");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[R2DER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("m");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[R3DER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("n");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[AIZQ]")>0) {
             //halloIZQ 
             AutoIZQ();                
      }
      else if (inString.indexOf("[HNIZQ1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(1,carrera[12],rampa[6],0,limLento,0);
      }
       else if (inString.indexOf("[HNIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(1,carrera[2],rampa[1],0,limLento,0);
      }
       else if (inString.indexOf("[HPIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(1,carrera[2],rampa[1],0,limLento,1);
      }
      else if (inString.indexOf("[HPIZQ1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(1,carrera[12],rampa[6],0,limLento,1);
      }
      else if (inString.indexOf("[VNIZQ1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(2,carrera[4],rampa[3],0,limLento,0);
      }
       else if (inString.indexOf("[VNIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(2,carrera[1],rampa[1],0,limLento,0);
      }
       else if (inString.indexOf("[VPIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(2,carrera[1],rampa[1],0,limLento,1);
      }
       else if (inString.indexOf("[VPIZQ1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(2,carrera[4],rampa[3],0,limLento,1);
      }
      else if (inString.indexOf("[TEIZQ]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(3,carrera[8],rampa[4],0,limLento,0);
        mimotor.mover1(3,carrera[8],rampa[4],0,limLento,1);
      }
       else if (inString.indexOf("[ACEN]")>0) {
          //halloCEN
          AutoCEN();
      }
      else if (inString.indexOf("[HNCEN1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(4,carrera[12],rampa[6],0,limLento,0);
      }
       else if (inString.indexOf("[HNCEN]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(4,carrera[2],rampa[1],0,limLento,0);
      }
       else if (inString.indexOf("[HPCEN]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(4,carrera[2],rampa[1],0,limLento,1);
      }
       else if (inString.indexOf("[HPCEN1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(4,carrera[12],rampa[6],0,limLento,1);
      }
      else if (inString.indexOf("[VNCEN1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(8,carrera[4],rampa[3],0,limLento,0);
      }
       else if (inString.indexOf("[VNCEN]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(8,carrera[1],rampa[1],0,limLento,0);
      }
       else if (inString.indexOf("[VPCEN]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(8,carrera[1],rampa[1],0,limLento,1);
      }
       else if (inString.indexOf("[VPCEN1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(8,carrera[4],rampa[3],0,limLento,1);
      }
      else if (inString.indexOf("[TECEN]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(12,carrera[8],rampa[4],0,limLento,0);
        mimotor.mover1(12,carrera[8],rampa[4],0,limLento,1);

      }
       else if (inString.indexOf("[ADER]")>0) {
            //halloDER
            AutoDER();
          
      }
      else if (inString.indexOf("[HNDER1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(16,carrera[12],rampa[6],0,limLento,0);
      }
       else if (inString.indexOf("[HNDER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(16,carrera[2],rampa[1],0,limLento,0);
      }
       else if (inString.indexOf("[HPDER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(16,carrera[2],rampa[1],0,limLento,1);
      }
       else if (inString.indexOf("[HPDER1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        mimotor.mover1(16,carrera[12],rampa[6],0,limLento,1);
      }
      else if (inString.indexOf("[VNDER1]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("s");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[VNDER]")>0) {
        //digitalWrite(PIN_LED, LOW);
        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("o");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
       else if (inString.indexOf("[VPDER]")>0) {
        //digitalWrite(PIN_LED, LOW);

        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("p");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
      else if (inString.indexOf("[VPDER1]")>0) {
        //digitalWrite(PIN_LED, LOW);

        
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("t");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
      }
    

        else if (inString.indexOf("[TEDER]")>0) {

         mimotor.mover1(16,carrera[8],rampa[4],0,limLento,0);
         mimotor.mover1(16,carrera[8],rampa[4],0,limLento,1);
                  Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("u");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
        
   
      }


 /*else if (inString.indexOf("[APAN]")>0) {

      }else if (inString.indexOf("[ATOT]")>0) {

      }*/


        else if (inString.indexOf("[AUP0]")>0) {
          AutoDER();
          AutoCEN();
          AutoIZQ();
         

        
   
      }
      else if (inString.indexOf("[AUP1]")>0) {

        
   
      }
      else if (inString.indexOf("[AUP2]")>0) {

    
        
   
      }
      else if (inString.indexOf("[AUP3]")>0) {

  
        
   
      }
      else if (inString.indexOf("[TOT0]")>0) {
              Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
              Wire.write("n");//regreso 3 derecha
              delay(10);
              Wire.write("r");
              Wire.endTransmission();
           
           for(int b=0;b<180;b++){
             //if(b<15){
             if(b<10){
                
                AutoDER(10);  
             }
             if(b<170){
              // AutoCEN(12,10);
              AutoCEN(12,1);
             }
             if(b<100){
              //AutoIZQ(60,10);  
              AutoIZQ(60,5);
             }
             delay(1);
           }
           
      }
      else if (inString.indexOf("[TOT1]")>0) {

        
   
      }
      else if (inString.indexOf("[TOT2]")>0) {

    
        
   
      }
      else if (inString.indexOf("[TOT3]")>0) {


   
      }

      else
      {
        Serial.println("Comando equivocado");
      }
      inString = "";
    }
  }
  //fin de esp 8266

  delay(600);

}


