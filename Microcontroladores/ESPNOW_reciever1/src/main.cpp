#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <string.h>
 // Rui Santos https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/

//#define x_paso 26    // Define el Pin de STEP para Motor de eje X
//#define x_dire 12   // Define el Pin de DIR  para Motor de eje X
//#define x_habi 27    // Define el Pin de ENABLE  para Motor de eje X


//#define x_paso 35    // Define el Pin de STEP para Motor de eje X
//#define x_dire 34   // Define el Pin de DIR  para Motor de eje X
//#define x_habi 32    // Define el Pin de ENABLE  para Motor de eje X

//#define x_dire 6   // Define el Pin de DIR  para Motor de eje X
//#define x_paso 7    // Define el Pin de STEP para Motor de eje X
//#define x_habi 8    // Define el Pin de ENABLE  para Motor de eje X

//#define x_dire 15   // Define el Pin de DIR  para Motor de eje X
//#define x_paso 2    // Define el Pin de STEP para Motor de eje X
//#define x_habi 0    // Define el Pin de ENABLE  para Motor de eje X



//#define x_dire 4   // Define el Pin de DIR  para Motor de eje X
//#define x_paso 0    // Define el Pin de STEP para Motor de eje X
//#define x_habi 2    // Define el Pin de ENABLE  para Motor de eje X

#define x_dire 2   // Define el Pin de DIR  para Motor de eje X
//#define x_dire 15   // Define el Pin de DIR  para Motor de eje X
#define x_paso 0    // Define el Pin de STEP para Motor de eje X
#define x_habi 4    // Define el Pin de ENABLE  para Motor de eje X

#define LED1 12





const int buttonPin0 = 34;  // pin asociado al boton 0
const int  buttonPin1 = 35;  //pin asociado al boton 1

int buttonState0 = 0;  // variable del estado del botOn
int buttonState1 = 0;  // variable del estado del botOn



//int retardo = 3000;   // Menor numero el giro es mas rapido
//int tiempo = 200;   // durante cuanto timpo da el giro el motor (vueltas)



void giro(int paso_,int dire_,int habi_,int dir,int retardo,int tiempo=200) {
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
  //digitalWrite(habi_, HIGH);   // quita la habilitacion del Driver
   digitalWrite(paso_, LOW); //maniente el motor es su posicion
   digitalWrite(dire_, LOW); //maniente el motor es su posicion

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

typedef struct struct_message
{
  char ESP32NowValues[33];
} struct_message;
struct_message ESP32NowMessage;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&ESP32NowMessage, incomingData, sizeof(ESP32NowMessage));
  Serial.println("Bytes received: " + String(len));
  Serial.println("Values:" + String(ESP32NowMessage.ESP32NowValues));
  Serial.println("---------------------------------------");
}

const char WiFiSSID[] = "SSID";
const char WiFiPassword[] = "PASSWORD";
//
void setup()
{

  
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  // WiFi.begin(WiFiSSID, WiFiPassword);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(x_paso, OUTPUT); pinMode(x_dire, OUTPUT); pinMode(x_habi, OUTPUT);  pinMode(buttonPin0, INPUT);   pinMode(buttonPin1, INPUT);   
    Serial.begin(115200);
    pinMode(LED1, OUTPUT);      // pin LED como salida

    delay(10);
}




void loop()
{

    // read the state of the pushbutton value:
  buttonState0 = digitalRead(buttonPin0);
    buttonState1 = digitalRead(buttonPin1);

 // Supongamos que recibes datos por ESP-NOW y los almacenas en una variable llamada "datosRecibidos"
  //String datosRecibidos = "Lectura 1: 501, Lectura 2: 734";
  String datosRecibidos =ESP32NowMessage.ESP32NowValues;
  
  // Encontrar el índice de los dos puntos para Lectura 1
  int indiceInicioLectura1 = datosRecibidos.indexOf(':') + 2;
  
  // Encontrar la coma después de Lectura 1
  int indiceFinLectura1 = datosRecibidos.indexOf(',', indiceInicioLectura1);
  
  // Extraer el substring correspondiente a Lectura 1
  String lectura1String = datosRecibidos.substring(indiceInicioLectura1, indiceFinLectura1);
  
  // Convertir la cadena a un valor entero
  int lectura1 = lectura1String.toInt();
  
  // Encontrar el índice de los dos puntos para Lectura 2
  int indiceInicioLectura2 = datosRecibidos.indexOf(':', indiceFinLectura1) + 2;
  
  // Extraer el substring correspondiente a Lectura 2
  String lectura2String = datosRecibidos.substring(indiceInicioLectura2);
  
  // Convertir la cadena a un valor entero
  int lectura2 = lectura2String.toInt();

   
  
  // Imprimir los valores obtenidos
  //Serial.print("Lectura 1: ");
  //Serial.println(lectura1);
  //Serial.print("Lectura 2: ");
  //Serial.println(lectura2);
  
  
//Serial.print(buttonState0);
//Serial.println(buttonState1);

  
        //afuera es 35 button pin 1 es afuera
        //Serial.println("boton1");
        if((buttonState0 == HIGH)||(buttonState1 == HIGH)){
            //digitalWrite(x_habi, HIGH);//INHABLITA MOTOR  
            if(buttonState0 == HIGH){

                 switch (lectura1)
                 {
                    case 300:
                      digitalWrite(x_habi, LOW); //HABLITA MOTOR
                      digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
                      giro(x_paso, x_dire, x_habi,LOW,2,3);
                      giro(x_paso, x_dire, x_habi,HIGH,2,3);        
                    break;
                    case 305:
                      digitalWrite(x_habi, LOW); 
                      //giro1(x_paso, x_dire, x_habi,HIGH,2,875,700,1);
                      //giro1(int paso_,int dire_,int habi_,int dir,int RAMP,int l_SUP,int l_INF,int tiempo=200)
                      giro1(x_paso, x_dire, x_habi,HIGH,2,875,825,1);
                   break;

                    case 306:
                     digitalWrite(x_habi, LOW); 
                     //giro1(x_paso, x_dire, x_habi,HIGH,6,875,775,2);
                     giro1(x_paso, x_dire, x_habi,HIGH,6,875,825,1000);
                    break;
      
                   case 307:
                     digitalWrite(x_habi, LOW); 
                     //giro1(x_paso, x_dire, x_habi,HIGH,6,875,775,4);
                     giro1(x_paso, x_dire, x_habi,HIGH,6,875,825,2500);
                   break;

                   case 308:
                      digitalWrite(x_habi, LOW); 
                      //giro1(x_paso, x_dire, x_habi,HIGH,6,875,775,8);
                      giro1(x_paso, x_dire, x_habi,HIGH,6,875,825,8000);
                    break;

                  default:
                    digitalWrite(x_habi, LOW); //HABLITA MOTOR
                    digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
                    giro(x_paso, x_dire, x_habi,LOW,2,3);//mini giro
                  giro(x_paso, x_dire, x_habi,HIGH,2,3);//mini giro
                  break;
           
                 }
                  /*if(lectura1==305){
                      //mueve derecha
                       digitalWrite(x_habi, LOW);
                       giro1(x_paso, x_dire, x_habi,HIGH,6,850,700,1);
                  }*/
            }
            if(buttonState1 == HIGH){
                 switch (lectura1)
                 {
                    case 300:
                      digitalWrite(x_habi, LOW); //HABLITA MOTOR
                      digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
                      giro(x_paso, x_dire, x_habi,LOW,2,3);
                      giro(x_paso, x_dire, x_habi,HIGH,2,3);        
                    break;

                    case 301:
                      digitalWrite(x_habi, LOW); 
                    //giro1(x_paso, x_dire, x_habi,LOW,6,875,775,8);
                    giro1(x_paso, x_dire, x_habi,LOW,6,875,825,8000);
            
                      
                    break;

                        case 302:
                      digitalWrite(x_habi, LOW); 
                      //giro1(x_paso, x_dire, x_habi,LOW,6,875,775,4);
                      giro1(x_paso, x_dire, x_habi,LOW,6,875,825,2500);
                  
                    break;

                    case 303:
                      digitalWrite(x_habi, LOW); 
                    //giro1(x_paso, x_dire, x_habi,LOW,6,875,775,2);
                    giro1(x_paso, x_dire, x_habi,LOW,6,875,825,1000);
                  
                    break;

                      case 304:
                      digitalWrite(x_habi, LOW); 
                      //giro1(x_paso, x_dire, x_habi,LOW,2,875,700,1);
                      giro1(x_paso, x_dire, x_habi,LOW,2,875,825,1);
                    
                    break;
                    
                        
                    default:
                      digitalWrite(x_habi, LOW); //HABLITA MOTOR
                      digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
                      giro(x_paso, x_dire, x_habi,LOW,2,3);//mini giro
                    giro(x_paso, x_dire, x_habi,HIGH,2,3);//mini giro
                    break;
                  }
                  /*if(lectura1==304){
                      //mueve izquierda
                      digitalWrite(x_habi, LOW); 
                      giro1(x_paso, x_dire, x_habi,LOW,6,850,700,1);
                  }*/
            }

        }else{
          switch(lectura1) {
            case 300:

             digitalWrite(x_habi, LOW); //HABLITA MOTOR
             digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
             giro(x_paso, x_dire, x_habi,LOW,2,3);
             giro(x_paso, x_dire, x_habi,HIGH,2,3);
                  
            break;

             case 303:
                digitalWrite(x_habi, LOW); 
              //giro1(x_paso, x_dire, x_habi,LOW,6,875,775,2);
               giro1(x_paso, x_dire, x_habi,LOW,6,875,825,1000);                
            break;


              case 304:
               digitalWrite(x_habi, LOW); 
              //giro1(x_paso, x_dire, x_habi,LOW,2,875,700,1);
              giro1(x_paso, x_dire, x_habi,LOW,2,875,825,1);
             
            break;
              //centro de mecanismo
             case 305:
              digitalWrite(x_habi, LOW); 
             //giro1(x_paso, x_dire, x_habi,HIGH,2,875,700,1);
             //giro1(x_paso, x_dire, x_habi,HIGH,2,875,775,1);
             giro1(x_paso, x_dire, x_habi,HIGH,2,875,825,1);
            

            break;

            case 306:
              digitalWrite(x_habi, LOW); 
             //giro1(x_paso, x_dire, x_habi,HIGH,6,875,775,2);
               giro1(x_paso, x_dire, x_habi,HIGH,6,875,825,1000);
            break;

            default:
              digitalWrite(x_habi, LOW); //HABLITA MOTOR
              digitalWrite(x_paso, HIGH); //maniente el motor es su posicion 
              giro(x_paso, x_dire, x_habi,LOW,2,3);//mini giro
             giro(x_paso, x_dire, x_habi,HIGH,2,3);//mini giro
            break;
           

          }
             
        }
        
      
}//fin loop




