#include <Arduino.h>//operaciones del marco de trabajo
#include <esp_now.h>//comunicacion inalAmbrica

#include <WiFi.h>//comunicacion inalAmbrica Dependencia directa
#include <Wire.h>//comunicacion I2C Dependencia directa

#include <stdio.h>
#include <string.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/Task.h"
//#include "esp_log.h"
//#include "driver/i2c.h"

#define I2C_ADDRESS 0x50 // Dirección I2C deseada para el dispositivo


//#define fotoRes0 33//SI HA FUNCIIONADO
//#define fotoRes0 34//SI HA FUNCIIONADO
//#define fotoRes0 35//SI HA FUNCIIONADO

#define fotoRes0 36//SI HA FUNCIIONADO
#define fotoRes1 39//SI HA FUNCIIONADO

#define x_dire 2   // Define el Pin de DIR  para Motor de eje X SI FUNCIONA
//#define x_dire 15   // Define el Pin de DIR  para Motor de eje X
#define x_paso 0    // Define el Pin de STEP para Motor de eje X
#define x_habi 4    // Define el Pin de ENABLE  para Motor de eje X

#define LED1 12

//intentar con 2 pines faltantes


int fotoRes0_val;
int fotoRes1_val;

int detectaSol=0;




//int right_x_val;
//int right_y_val; 


const int buttonPin0 = 34;  // the number of the pushbutton pin
const int  buttonPin1 = 35;  // the number of the pushbutton pin
int buttonState0 = 0;  // variable for reading the pushbutton status

int buttonState1 = 0;  // variable for reading the pushbutton status

int value = 0;

//int tiempo = 200;   // durante cuanto timpo da el giro el motor (vueltas)


//int right_x_val;
//int right_y_val; 

int etapas =1;
String cadena0, cadena1;

int i2espNOW_val;
//int* ptrGlobal;

int tiempo = 200;   // durante cuanto timpo da el giro el motor (vueltas)


// Rui Santos https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
//uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xAA, 0x84, 0x10};
//C8:F0:9E:A0:7F:04
//uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xA0, 0x7F, 0x04};

//FC:B4:67:F1:23:40
//uint8_t broadcastAddress[] = {0xFC, 0xB4, 0x67, 0xF1, 0x23, 0x40};


//D4:8A:FC:C9:A8:5C
//uint8_t broadcastAddress[] = {0xFC, 0xB4, 0x67, 0xF1, 0x23, 0x40};

//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xC9,0xA8,0x5C};

//FC:B4:67:F1:23:40
//uint8_t broadcastAddress[] = {0xFC,0xB4,0x67,0xF1,0x23,0x40};


//D4:8A:FC:CC:9C:0C
//D4:8A:FC:CC:9C:0C //SUPERVIVIENTE
//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xCC,0x9C,0x0C};

//D4:8A:FC:CC:D4:98
//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xCC,0xD4,0x98};

//D4:8A:FC:C9:A8:5C
//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xC9,0xA8,0x5C};

//D4:8A:FC:A6:37:D4
//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xA6,0x37,0xD4};

//D4:8A:FC:A6:B1:70
//uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xA6,0xB1,0x70};

//D4:8A:FC:9F:34:A4
uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0x9F,0x34,0xA4};

typedef struct struct_message
{
  char ESP32NowText[33];
} struct_message;
struct_message ESP32NowMessage;
//
//String text = "AAA000010000200003000040000500006";
String text(23);
esp_now_peer_info_t peerInfo;
// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}



void giro(int paso_,int dire_,int habi_,int dir,int retardo,int tiempo) {
   digitalWrite(habi_, LOW);  // Habilita el Driver
  if( dir==0){ 
   digitalWrite(dire_, LOW);   // direccion de giro 0
   for(int i=0;i<tiempo;i++){  // da  pasos por un tiempo  
    digitalWrite(paso_, HIGH);      
    delayMicroseconds(retardo);          
    digitalWrite(paso_, LOW);       
    delayMicroseconds(retardo); 
   }
  }
  else if( dir==1){ 
  digitalWrite(dire_, HIGH);   // direccion de giro 1
  for(int i=0;i<tiempo;i++){   // da  pasos por un tiempo  
 
        delayMicroseconds(retardo); 
        digitalWrite(paso_, LOW); 
        delayMicroseconds(retardo);  
       digitalWrite(paso_, HIGH);      
    //     el orden de la onda cuadrada no altera el giro   

   }
  }
  digitalWrite(habi_, HIGH);   // remueve la habilitacion del Driver

   

}



void giro1(int paso_,int dire_,int habi_,int dir,int RAMP,int l_SUP,int l_INF,int tiempo=200){

  //rampa ascendente
                  for(int g=l_SUP;g>l_INF;g--){
                      //mover(motor,g,ramp,dir);
                      giro(paso_, dire_, habi_, dir,g,RAMP);//vel,tiempo
                      //delay(1000);
                  }
   
                giro(paso_, dire_, habi_, dir,l_INF,tiempo);//vel,tiempo
              //
              for(int g=l_INF;g<l_SUP;g++){
                 //mover(motor,g,ramp,dir);
                 giro(paso_,dire_, habi_, dir, g,RAMP);//vel,tiempo
              }
}


void lecturas(){
  String cadena = "Lectura 0: " + String(fotoRes0_val) + ", Lectura 1: " + String(fotoRes1_val);
  //Serial.println(cadena);
}

// Función para manejar las solicitudes del maestro
void requestEvent() {
  //int value1 = analogRead(pin1); // Lee el valor analógico del pin 1
  //int value2 = analogRead(pin2); // Lee el valor analógico del pin 2
  
  //Wire.write((byte)fotoRes0_val); // Envía el primer byte de la lectura analógica al maestro
  //Wire.write((byte)fotoRes1_val); // Envía el segundo byte de la lectura analógica al maestro
  // Envía las lecturas analógicas al maestro (Arduino Mega)
  //Wire.write( fotoRes0_val >> 8); // Envía el byte más significativo primero
  //Wire.write( fotoRes0_val & 0xFF); // Envía el byte menos significativo
  //Wire.write( fotoRes1_val >> 8);
  //Wire.write( fotoRes1_val & 0xFF);

  //Wire.write(highByte(fotoRes0_val)); // Envía el byte más significativo primero
  //Wire.write(lowByte(fotoRes0_val)); // Envía el byte menos significativo
  //Wire.write(highByte(fotoRes1_val));
  //Wire.write(lowByte(fotoRes1_val));
}



void llegaDato(int bytes) {
 
 //int retINICIO=10;
 //int retFIN=60;

 
 int retINICIO=20;
 int retFIN=80;
  while (Wire.available()) {
    char comando = Wire.read();
    delay(100);
    switch (comando)
    {
       case 'a':
       detectaSol=0;
        //Serial.println("wire(A)");
         digitalWrite(16,HIGH);
         delay(400);
        break;
        case 'b':
        detectaSol=0;
        //Serial.println("wire(B)");
         digitalWrite(16,LOW);
         delay(400);
        break;
        case 'c':
        detectaSol=0;
        //Serial.println("wire(C)");
         //giro(x_paso,x_dire,x_habi,HIGH,3000,50);
         delay(400);
        break;
      case 'd':
      detectaSol=0;
        // Leer las lecturas analógicas y enviarlas al maestro
        fotoRes0_val = analogRead(fotoRes0);
        fotoRes1_val = analogRead(fotoRes1);
        
        Wire.write(50);
        Wire.write(40);
        delay(500);
        break;

      case 'g':
      detectaSol=0;
        i2espNOW_val=1;
        delay(retINICIO);
        //Serial.print("wire(G):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'h':
       detectaSol=0;
        i2espNOW_val=2;
        delay(retINICIO);
        //Serial.print("wire(H):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'i':
       detectaSol=0;
       i2espNOW_val=3;
       delay(retINICIO);
        //Serial.print("wire(I):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'j':
       detectaSol=0;
       i2espNOW_val=4;
       delay(retINICIO);
        //Serial.print("wire(J):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'k':
       detectaSol=0;
       i2espNOW_val=5;
       delay(retINICIO);
        //Serial.print("wire(K):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'l':
       detectaSol=0;
           i2espNOW_val=6;
           delay(retINICIO);
        //Serial.print("wire(L):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'm':
       detectaSol=0;
        i2espNOW_val=7;
        delay(retINICIO);
        //Serial.print("wire(M):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;

       case 'n':
       detectaSol=0;
        i2espNOW_val=8;
        delay(retINICIO);
        //Serial.print("wire(N):");
        //Serial.println(i2espNOW_val);
        delay(retFIN);
       break;
      
      case 'o':
      detectaSol=0;
        //Serial.println("motorLado1");
        //giro(x_paso,x_dire,x_habi,HIGH,3000,50);
        giro(x_paso,x_dire,x_habi,HIGH,3000,75);
        //giro(x_paso,x_dire,x_habi,HIGH,3000,100);
        delay(400);
       break;

      case 'p':
      detectaSol=0;
        //Serial.println("motorLado2");
        //giro(x_paso,x_dire,x_habi,LOW,3000,50);
        giro(x_paso,x_dire,x_habi,LOW,3000,75);
        //giro(x_paso,x_dire,x_habi,LOW,3000,100);
        delay(400);
      break;

       case 'q':

       //###### CASO SEGUIDOR SOLAR####
       
        //i2espNOW_val=9;
        //delay(400);

        //giro1(x_paso,x_dire,x_habi,HIGH,1,950,800,1);
        //giro1(x_paso,x_dire,x_habi,LOW,1,950,800,1);

         detectaSol=1;

        
      break;

      case 'r':
      detectaSol=0;
        i2espNOW_val=0;
        delay(400);
      break;

      case 's':
      detectaSol=0;
        //Serial.println("motorLado1");
        //giro(x_paso,x_dire,x_habi,HIGH,3000,100);
        //void giro1(int paso_,int dire_,int habi_,int dir,int RAMP,int l_SUP,int l_INF,int tiempo=200)
        giro1(x_paso,x_dire,x_habi,HIGH,1,1000,600,1);
        delay(400);
      break;

      case 't':
      detectaSol=0;
           //Serial.println("motorLado2");
        //giro(x_paso,x_dire,x_habi,LOW,3000,100);
        giro1(x_paso,x_dire,x_habi,LOW,1,950,800,1);
        delay(400);
      break;

      case 'u':
      detectaSol=0;
           //Serial.println("motorLado2");
        //giro(x_paso,x_dire,x_habi,LOW,3000,100);
        giro1(x_paso,x_dire,x_habi,HIGH,1,950,800,1);
        giro1(x_paso,x_dire,x_habi,LOW,1,950,800,1);
        delay(400);
      break;
    
      default:
      detectaSol=0;
        comando= 'r';
      break;
    }
    
    /*if (command == 'l') {
      // Leer las lecturas analógicas y enviarlas al maestro
      fotoRes0_val = analogRead(fotoRes0);
      fotoRes1_val = analogRead(fotoRes1);
      
      Wire.write(50);
      Wire.write(40);
    }*/
  }

  /*while (Wire.available()) {
    Wire.read(); // Descarta el comando recibido (no se utiliza)
    fotoRes0_val = analogRead(fotoRes0); // Lee las lecturas analógicas
    fotoRes1_val = analogRead(fotoRes1);
    Wire.write(fotoRes0_val); // Envía las lecturas analógicas al maestro
    Wire.write(fotoRes1_val);
  }*/
}





void setup()
{

   pinMode(x_paso, OUTPUT); pinMode(x_dire, OUTPUT); pinMode(x_habi, OUTPUT);  pinMode(buttonPin0, INPUT);   pinMode(buttonPin1, INPUT);   

    pinMode(LED1, OUTPUT);      // set the LED pin mode
    pinMode(16, OUTPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    //Serial.println("Error inicializando ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    //Serial.println("Fallo al agregar a peer");
    return;
  }


 //  pinMode(fotoRes1, INPUT);
 // pinMode(fotoRes0, INPUT);
 // pinMode(Right_VRX_PIN, INPUT);
 // pinMode(Right_VRX_PIN, INPUT);

  Wire.begin(I2C_ADDRESS); // Inicia la comunicación I2C con la direcciOn especificada
  Wire.onRequest(requestEvent); // Define la función para manejar las solicitudes del maestro
  Wire.onReceive(llegaDato); // Registramos el evento al recibir datos

    delay(10);
}

void loop()
{

 // Cálculo del error
      int error = fotoRes0_val - fotoRes1_val;
      int precision =200;

 fotoRes0_val = analogRead(fotoRes0); //LECTURAS ANALOGICAS
  fotoRes1_val = analogRead(fotoRes1); //LECTURAS ANALOGICAS
 
  // read the state of the pushbutton value:
  buttonState0 = digitalRead(buttonPin0);
    buttonState1 = digitalRead(buttonPin1);



  // Imprimir valores en el monitor serial (opcional)
  Serial.print("IZQ:");
  Serial.print(fotoRes0_val);
  Serial.print("DER:");
  Serial.println(fotoRes1_val);
  //Serial.print(" Error: ");
  //Serial.println(error);
  
   //Wire.onRequest(requestEvent); // Define la función para manejar las solicitudes del maestro
   //Wire.onReceive(llegaDato); // Registramos el evento al recibir datos
 


             switch (i2espNOW_val)
              {
              case 1:
              //Serial.println("CASO 1");
              //digitalWrite(16,HIGH);
              //giro(x_paso,x_dire,x_habi,HIGH,3000);
                cadena0 = "301";
                cadena1 = "301";
                //lecturas();
                //etapas=2;
                break;

                case 2:
                //Serial.println("CASO 2");
                //digitalWrite(16,LOW);
                cadena0 = "302";
                cadena1 = "302";
                //lecturas();
                //etapas=3;
                break;

                case 3:
                //Serial.println("CASO 3");
                cadena0 = "303";
                cadena1 = "303";
                //lecturas();
                //etapas=4;
                break;

                case 4:
                //Serial.println("CASO 4");
                cadena0 = "304";
                cadena1 = "304";
                //lecturas();
                //etapas=5;
                break;

              case 5:
              //Serial.println("CASO 5");
                cadena0 = "305";
                cadena1 = "305";
                //lecturas();
                //etapas=6;
                break;

                case 6:
                //Serial.println("CASO 6");
                cadena0 = "306";
                cadena1 = "306";
                //lecturas();
                //etapas=7;
                break;

                case 7:
                  //Serial.println("CASO 7");
                  cadena0 = "307";
                  cadena1 = "307";

                
                   // etapas=0;
                  break;

                  case 8:
                  //Serial.println("CASO 8");
                  cadena0 = "308";
                  cadena1 = "308";

                
                 //   etapas=0;
                  break;

                  case 9:
                  //Serial.println("CASO 9");
                  cadena0 = "309";
                  cadena1 = "309";
     
                
                 //   etapas=0;
                  break;

                case 0:
                //Serial.println("CASO 0");
                cadena0 = "300";
                cadena1 = "300";
                //lecturas();
                //etapas=1;
                break;

              default:
                break;
              }


              if(detectaSol==1){

                    delay(10);

                    fotoRes0_val = analogRead(fotoRes0);
                    fotoRes1_val = analogRead(fotoRes1);

                      //if(abs(fotoRes0_val - fotoRes1_val) > 1){
                              if (fotoRes0_val < fotoRes1_val) {
                            //sentido 
                       //     (int motor, int motPausa, int rep, int dir)
                         //         mimotor.mover(2,5,6,0); 
                              //giro(int paso_,int dire_,int habi_,int dir,int retardo,int tiempo);
                              //mimotor.mover(16,10,12,1);  
                              //giro(x_paso,x_dire,x_habi,HIGH,10,12);
                              //giro(x_paso,x_dire,x_habi,HIGH,3000,50);
                              //giro(x_paso,x_dire,x_habi,HIGH,5,6);
                              giro(x_paso,x_dire,x_habi,HIGH,3000,200);
                              //Serial.println("positivo");
                          }
                          else{
                              //sentido 
                                //mimotor.mover(16,10,12,0); 
                                //giro(x_paso,x_dire,x_habi,LOW,10,12);
                                //giro(x_paso,x_dire,x_habi,LOW,3000,50);
                                //giro(x_paso,x_dire,x_habi,LOW,5,6);
                                giro(x_paso,x_dire,x_habi,LOW,3000,200);
                                //Serial.println("negativo");
              
                          }
                     // }else{
                       //     detectaSol=0;

                     // }
                            
              }



 text.remove(0);
delay(10);


 text.concat("Sen1: ");
 text.concat(cadena0);
  text.concat(", Sen2: ");
  text.concat(cadena1);



  strncpy(ESP32NowMessage.ESP32NowText, text.c_str(), text.length());
  //Serial.println("Msg to send:" + String(ESP32NowMessage.ESP32NowText));
    //Serial.println(String(ESP32NowMessage.ESP32NowText));
  //Serial.println("Snd Len:" + String(sizeof(ESP32NowMessage)));
    // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&ESP32NowMessage, sizeof(ESP32NowMessage));
  if (result == ESP_OK)
  {
    //Serial.println("Sent with success");
  }
  else
  {
    //Serial.println("Error sending the data");
  }
 
  //delay(1000);
  delay(40);


}