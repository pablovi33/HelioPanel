
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


void setup() {
  // InicializaciOn de puertos y salidas
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  
   pinMode(3,INPUT);
   
  digitalWrite(PIN_LED, LOW);

  Wire.begin();

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
        
        //int Verde_AF2 = analogRead(A3);
        //int Amarillo_AF2 = analogRead(A4);
        //int Azul_AF2 = analogRead(A5);
        //int Naranja_AF2 = analogRead(A9);

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
        //int AF0_0 = map(AF0_0_n, 3, 1016, 0, 600);
        //int AF0_1 = map(AF0_1_n, 50, 990, 0, 600);
        //int AF0_2 = map(AF0_2_n, 15, 1000, 0, 600);
        //int AF0_3 = map(AF0_3_n, 7, 1012, 0, 600);

        int AF0_0 = map(AF0_0_n, 16, 950, 0, 600);
        int AF0_1 = map(AF0_1_n, 97, 990, 0, 600);
        int AF0_2 = map(AF0_2_n, 40, 1000, 0, 600);
        int AF0_3 = map(AF0_3_n, 20, 1012, 0, 600);

//Variables para panel Derecha
        int AF1_A =  map(AF1_A_n, 70, 1023, 0, 600);
        int AF1_B =  map(AF1_B_n, 130, 985, 0, 600);

//Variables para panel Central
        int AF2_0 =  map(AF2_0_n, 20, 1000, 0, 600);//
        int AF2_1 =  map(AF2_1_n, 68, 950, 0, 600);
        int AF2_2 =  map(AF2_2_n, 19, 1023, 0, 600);
        int AF2_3 =  map(AF2_3_n, 16, 1023, 0, 600);


        
       

        // impresion de datos en monitor serial:
int selPrint = 3;

        //Serial.println("######################################");

  switch (selPrint)
  {
  case 1:
    Serial.print("AF0_0:");
          Serial.print(AF0_0);
          Serial.print("  AF0_1: ");
          Serial.print(AF0_1);
          Serial.print("  AF0_2: ");
          Serial.print(AF0_2);
          Serial.print("  AF0_3: ");
          Serial.println(AF0_3);
          break;

  case 2:
 // impresion de datos en monitor serial:
        Serial.print("AF1_A:");
        Serial.print(AF1_A);
        Serial.print("  AF1_B: ");
        Serial.println(AF1_B);
        break;

  case 3:
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
        

        
  
  //      Serial.println("######################################");

        delay(1);  // retraso de estabilidad

        


    //Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
    //Wire.write("a");
    //Wire.endTransmission();
}

// Verificacion de la conectividad entre la Mega y ESP8266
void serialEvent3() {


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
        int AF0_0 = map(AF0_0_n, 3, 1016, 0, 600);
        int AF0_1 = map(AF0_1_n, 50, 990, 0, 600);
        int AF0_2 = map(AF0_2_n, 15, 1000, 0, 600);
        int AF0_3 = map(AF0_3_n, 7, 1012, 0, 600);

//Variables para panel Derecha
        int AF1_A =  map(AF1_A_n, 70, 1023, 0, 600);
        int AF1_B =  map(AF1_B_n, 130, 985, 0, 600);

//Variables para panel Central
       //Variables para panel Central
        int AF2_0 =  map(AF2_0_n, 20, 1000, 0, 600);//
        int AF2_1 =  map(AF2_1_n, 68, 950, 0, 600);
        int AF2_2 =  map(AF2_2_n, 19, 1023, 0, 600);
        int AF2_3 =  map(AF2_3_n, 16, 1023, 0, 600);


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

          //Ajuste automAtico del Panel Izquierda

          //movimiento Vertical
            do{
                 if(((AF0_0+AF0_2)/2)<((AF0_1+AF0_3)/2)){
                  //sentido 
                  mimotor.mover1(2,carrera[2],rampa[1],0,limLento,0);      
                }
                else{
                    //sentido
                  mimotor.mover1(2,carrera[2],rampa[1],0,limLento,1);
                    
                }
                
          }while (abs(((AF0_0+AF0_2)/2)-((AF0_1+AF0_3)/2))>110);
          
          
                //movimiento Horizontal
          do{
                  if(((AF0_2+AF0_3)/2)<((AF0_0+AF0_1)/2)){
                    //sentido 
                    mimotor.mover1(1,carrera[2],rampa[1],0,limLento,0);
                  }
                  else{
                    //sentido 
                    mimotor.mover1(1,carrera[2],rampa[1],0,limLento,1);
                  }
          }while (abs(((AF0_2+AF0_3)/2)-((AF0_1+AF0_0)/2))>110);
          
                 
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
          
          //Ajuste automAtico del Panel Central
          int contador =0;
          //movimiento Vertical
            do{
              if(contador<5){
                  if(AF2_3<AF2_2){
                    //sentido 
                    mimotor.mover1(8,carrera[2],rampa[1],0,limLento,0);      
                  }
                  else{
                      //sentido
                    mimotor.mover1(8,carrera[2],rampa[1],0,limLento,1);
                      
                  }
                delay(400);
                contador++;
              }  
          }while ((abs(AF2_3-AF2_2)>80)||(contador==5));
          
          contador=0;
                //movimiento Horizontal
          do{
             if(contador<5){
                  if(AF2_0<AF2_2){
                    //sentido 
                    mimotor.mover1(4,carrera[2],rampa[1],0,limLento,0);
                  }
                  else{
                    //sentido 
                    mimotor.mover1(4,carrera[2],rampa[1],0,limLento,1);
                  }
                  delay(400);
                  contador++;
             }
          }while ((abs(AF2_0-AF2_2)>80)||(contador==5));
          
                 


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
        //digitalWrite(PIN_LED, LOW);
         Wire.beginTransmission(0x50);  // Transmite al Esclavo 0x50
         Wire.write("q");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();

               //movimiento Horizontal
               do
               {
                if(AF1_A>AF1_B){
                      //sentido aparentemente positivo
                      mimotor.mover1(16,carrera[2],rampa[1],0,limLento,1);
                  }
                  else{
                    //sentido aparentemente negativo
                    mimotor.mover1(16,carrera[2],rampa[1],0,limLento,0);
                  }

               } while (abs(AF1_A-AF1_B)>110);
               
                //fin movimiento Horizontal
          
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
         Wire.write("p");
         delay(10);
         Wire.write("r");
          Wire.endTransmission();
        
   
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


