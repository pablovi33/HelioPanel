#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <stdbool.h>




//IPAddress ip(192, 168, 1, 123); // Dirección IP estática
//192.168.30.248
//IPAddress ip(192, 168, 30, 248); // Dirección IP estática
//IPAddress ip(192, 168, 234, 248); // Dirección IP estática
//IPAddress ip(192, 168, 1, 184); // Dirección IP estática
//IPAddress ip(192, 168, 220, 240); // Dirección IP estática
//IPAddress ip(192, 168, 104, 248); // Dirección IP estática
//IPAddress ip(192, 168, 42, 248); // Dirección IP estática
//IPAddress ip(192, 168, 1, 248); // Dirección IP estática

IPAddress ip(192, 168, 110, 248); // Dirección IP estática
IPAddress gateway(192, 168, 1, 1); // Puerta de enlace
IPAddress subnet(255, 255, 255, 0); // Máscara de subred
IPAddress primarioDNS(8, 8, 8, 8);   //Servidor DNS opcional
IPAddress secundarioDNS(8, 8, 4, 4); //Servidor DNS optional
     
// Intorducir el nombre y la vontraseña de la red Wifi:
//const char* ssid     = "IDEA_1.61_salon";  // <- Cambiar por el nombre de su Red WiFi   
//const char* ssid     = "idea161";  // <- Cambiar por el nombre de su Red WiFi                                                                                                                                                                                                             <
//const char* password = "hazloenidea";  // <- Cambiar por la clave de su Red WiFi 

//const char* ssid     = "helio_centro_control";  // <- Cambiar por el nombre de su Red WiFi    
const char* ssid     = "HelioPanel";  // <- Cambiar por el nombre de su Red WiFi                                                                                                                                                                                                           <
const char* password = "12helio34";  // <- Cambiar por la clave de su Red WiFi 

ESP8266WebServer server(80);

const int buttonPin = 2; // Pin donde está conectado el botón en el Arduino Uno
//bool banderaB_0;

MDNSResponder mdns;
     
String webPage = "";
    
int led_pin = 13;
   
void setup(void){
     
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  Serial.begin(115200);
  while (!Serial) {
    ; // espera al puerto serial a conectarse. Necesario para puerto USB nativo solamente
  }

  pinMode(buttonPin, INPUT);



  

  Serial.println("");
  Serial.println("ESP8266 board info:");
  Serial.print("\tChip ID: ");
  Serial.println(ESP.getFlashChipId());
  Serial.print("\tCore Version: ");
  Serial.println(ESP.getCoreVersion());
  Serial.print("\tChip Real Size: ");
  Serial.println(ESP.getFlashChipRealSize());
  Serial.print("\tChip Flash Size: ");
  Serial.println(ESP.getFlashChipSize());
  Serial.print("\tChip Flash Speed: ");
  Serial.println(ESP.getFlashChipSpeed());
  Serial.print("\tChip Speed: ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("\tChip Mode: ");
  Serial.println(ESP.getFlashChipMode());
  Serial.print("\tSketch Size: ");
  Serial.println(ESP.getSketchSize());
  Serial.print("\tSketch Free Space: ");
  Serial.println(ESP.getFreeSketchSpace());


  webPage += "<h2>Interfaz Heliodon & Paneles</h2>";
 
  //webPage += "<p>LED state <a href=\"LedON\"><button>ON</button></a>&nbsp;<a href=\"LedOFF\"><button>OFF</button></a></p>";

  webPage += "<h3>Modulo Sol</h3>";

  webPage += "<p>|<a href=\"Reg3_IZQ\"><button>Re_3</button></a>&nbsp;<a href=\"Reg2_IZQ\"><button>Re_2</button></a>&nbsp;<a href=\"Reg1_IZQ\"><button>Re_1</button></a>&nbsp;<a href=\"Inc_IZQ\"><button>Inc</button></a>&nbsp;o<a href=\"Inc_DER\"><button>Inc</button></a>&nbsp;<a href=\"Reg1_DER\"><button>Re_1</button></a>&nbsp;<a href=\"Reg2_DER\"><button>Re_2</button></a>&nbsp;<a href=\"Reg3_DER\"><button>Re_3</button></a></p>";
      
  webPage += "<h3>Panel Izquierda</h3>";

  webPage += "<p>|<a href=\"AutoIZQ\"><button>Auto</button></a>&nbsp;||<a href=\"movHnegIZQ1\"><button>mov_H--</button></a>&nbsp;<a href=\"movHnegIZQ\"><button>mov_H-</button></a>&nbsp;o<a href=\"movHposIZQ\"><button>mov_H+</button></a>&nbsp;<a href=\"movHposIZQ1\"><button>mov_H++</button></a>&nbsp;||<a href=\"movVnegIZQ1\"><button>mov_V--</button></a>&nbsp;<a href=\"movVnegIZQ\"><button>mov_V-</button></a>&nbsp;o<a href=\"movVposIZQ\"><button>mov_V+</button></a>&nbsp;<a href=\"movVposIZQ1\"><button>mov_V++</button></a>&nbsp;||<a href=\"testingIZQ\"><button>TEST</button></a></p>";
      
  webPage += "<h3>Panel Central</h3>";

  webPage += "<p>|<a href=\"AutoCEN\"><button>Auto</button></a>&nbsp;||<a href=\"movHnegCEN1\"><button>mov_H--</button></a>&nbsp;<a href=\"movHnegCEN\"><button>mov_H-</button></a>&nbsp;o<a href=\"movHposCEN\"><button>mov_H+</button></a>&nbsp;<a href=\"movHposCEN1\"><button>mov_H++</button></a>&nbsp;||<a href=\"movVnegCEN1\"><button>mov_V--</button></a>&nbsp;<a href=\"movVnegCEN\"><button>mov_V-</button></a>&nbsp;o<a href=\"movVposCEN\"><button>mov_V+</button></a>&nbsp;<a href=\"movVposCEN1\"><button>mov_V++</button></a>&nbsp;||<a href=\"testingCEN\"><button>TEST</button></a></p>";
      
  webPage += "<h3>Panel Derecha</h3>";

  webPage += "<p>|<a href=\"AutoDER\"><button>Auto</button></a>&nbsp;||<a href=\"movHnegDER1\"><button>mov_H--</button></a>&nbsp;<a href=\"movHnegDER\"><button>mov_H-</button></a>&nbsp;o<a href=\"movHposDER\"><button>mov_H+</button></a>&nbsp;<a href=\"movHposDER1\"><button>mov_H++</button></a>&nbsp;||<a href=\"movVnegDER1\"><button>mov_V--</button></a>&nbsp;<a href=\"movVnegDER\"><button>mov_V-</button></a>&nbsp;o<a href=\"movVposDER\"><button>mov_V+</button></a>&nbsp;<a href=\"movVposDER1\"><button>mov_V++</button></a>&nbsp;||<a href=\"testingDER\"><button>TEST</button></a></p>";
      

webPage += "<h4>ESP8266 Info</h4>";

   webPage += "<p>Chip ID: ";
  webPage += ESP.getFlashChipId();
  webPage += "</p>";
  webPage += "<p>Core Version: ";
  webPage += ESP.getCoreVersion();
  webPage += "</p>";
  webPage += "<p>Chip Real Size: ";
  webPage += ESP.getFlashChipRealSize()/1024;
  webPage += " Kbit</p>";
  webPage += "<p>Chip Size: ";
  webPage += ESP.getFlashChipSize()/1024;
  webPage += " Kbit</p>";
  webPage += "<p>Chip Flash Speed: ";
  webPage += ESP.getFlashChipSpeed()/1000000;
  webPage += " MHz</p>";
  webPage += "<p>Chip Work Speed: ";
  webPage += ESP.getCpuFreqMHz();
  webPage += " MHz</p>";
  webPage += "<p>Chip Mode: ";
  webPage += ESP.getFlashChipMode();
  webPage += "</p>";

  WiFi.begin(ssid, password);
  Serial.println("");
     
  // Sacamos por el puerto serie la informacion de donde se conecta nuestro ESP8266
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }


  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Configures static IP address
  if (WiFi.status() != WL_CONNECTED) {
  Serial.println("Failed to connect to configured WiFi network using static IP");
}


  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

     // Configures static IP address
  if (!WiFi.config(ip, gateway, subnet, primarioDNS, secundarioDNS)) {
    Serial.println("STA Failed to configure");
  }
     
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  server.on("/LedON", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, HIGH);
    //banderaB_0=true;
    Serial.println("[ON]");
   delay(10);
  });
  
  server.on("/LedOFF", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[OFF]");

    //delay(1000);
    delay(10);
  });

  server.on("/Reg3_IZQ", [](){
    server.send(200, "text/html", webPage);
    //digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R3IZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/Reg2_IZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R2IZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/Reg1_IZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R1IZQ]");

    //delay(1000);
    delay(10);
  });


   server.on("/Inc_IZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[IIZQ]");

    //delay(1000);
    delay(10);
  });


   server.on("/Inc_DER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[IDER]");

    //delay(1000);
    delay(10);
  });


   server.on("/Reg1_DER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R1DER]");

    //delay(1000);
    delay(10);
  });

   server.on("/Reg2_DER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R2DER]");

    //delay(1000);
    delay(10);
  });


   server.on("/Reg3_DER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[R3DER]");

    //delay(1000);
    delay(10);
  });

   server.on("/AutoIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[AIZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHnegIZQ1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNIZQ1]");

    //delay(1000);
    delay(10);
  });


   server.on("/movHnegIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNIZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHposIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPIZQ]");

    //delay(1000);
    delay(10);
  });

  
   server.on("/movHposIZQ1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPIZQ1]");

    //delay(1000);
    delay(10);
  });


   server.on("/movVnegIZQ1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNIZQ1]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVnegIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNIZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVposIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPIZQ]");

    //delay(1000);
    delay(10);
  });

  
   server.on("/movVposIZQ1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPIZQ1]");

    //delay(1000);
    delay(10);
  });

  server.on("/testingIZQ", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TEIZQ]");

    //delay(1000);
    delay(10);
  });

   server.on("/AutoCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[ACEN]");

    //delay(1000);
    delay(10);
  });


   server.on("/movHnegCEN1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNCEN1]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHnegCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNCEN]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHposCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPCEN]");

    //delay(1000);
    delay(10);
  });


   server.on("/movHposCEN1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPCEN1]");

    //delay(1000);
    delay(10);
  });


   server.on("/movVnegCEN1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNCEN1]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVnegCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNCEN]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVposCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPCEN]");

    //delay(1000);
    delay(10);
  });


   server.on("/movVposCEN1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPCEN1]");

    //delay(1000);
    delay(10);
  });

  server.on("/testingCEN", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TECEN]");

    //delay(1000);
    delay(10);
  });

   server.on("/AutoDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[ADER]");

    //delay(1000);
    delay(10);
  });


   server.on("/movHnegDER1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNDER1]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHnegDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HNDER]");

    //delay(1000);
    delay(10);
  });

   server.on("/movHposDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPDER]");

    //delay(1000);
    delay(10);
  });


   server.on("/movHposDER1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[HPDER1]");

    //delay(1000);
    delay(10);
  });


   server.on("/movVnegDER1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNDER1]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVnegDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VNDER]");

    //delay(1000);
    delay(10);
  });

   server.on("/movVposDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPDER]");

    //delay(1000);
    delay(10);
  });


   server.on("/movVposDER1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[VPDER1]");

    //delay(1000);
    delay(10);
  });

  server.on("/testingDER", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TEDER]");

    //delay(1000);
    delay(10);
  });


  server.begin();
  Serial.println("HTTP server started");
  
}
     
 void loop(void){
 server.handleClient();

}
