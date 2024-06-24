#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <stdbool.h>


IPAddress ip(192, 168, 110, 248); // Dirección IP estática
IPAddress gateway(192, 168, 1, 1); // Puerta de enlace
IPAddress subnet(255, 255, 255, 0); // Máscara de subred
IPAddress primarioDNS(8, 8, 8, 8);   //Servidor DNS opcional
IPAddress secundarioDNS(8, 8, 4, 4); //Servidor DNS optional
     
// Intorducir el nombre y la vontraseña de la red Wifi:
//const char* ssid     = "IDEA_1.61_salon";  // <- Cambiar por el nombre de su Red WiFi   
//const char* ssid     = "idea161";  // <- Cambiar por el nombre de su Red WiFi                                                                                                                                                                                                             <
//const char* password = "hazloenidea";  // <- Cambiar por la clave de su Red WiFi 

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
 

//webPage += "<h3>Interfaz Heliodon & Paneles</h3>";


webPage += "<table><tr>";
webPage += "<td><h4>Modulo Sol</h4></td>";
//webPage += "<td>||<a href=\"testingCEN\"><button>TEST</button></a>&nbsp;||</td>";
webPage += "<td><a href=\"Reg3_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>|&lArr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Reg2_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Reg1_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Inc_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Inc_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Reg1_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Reg2_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>";
webPage += "<td><a href=\"Reg3_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;|</h3></button></a>&nbsp;</td>";

webPage += "    <td><a href=\"AutoPanel\"><button style=\"font-size: 20px; padding: 10px 20px;\">AutoPanel</button></a>&nbsp;</td>"; 
//webPage += "    <td><a href=\"AutoPanel_2\"><button style=\"font-size: 20px; padding: 10px 20px;\">Auto_2</button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"Total\"><button style=\"font-size: 20px; padding: 10px 20px;\">Total</button></a></td>"; 
//webPage += "    <td><a href=\"Total_2\"><button style=\"font-size: 20px; padding: 10px 20px;\">TOT_2</button></a></td>"; 

webPage += "</tr></table>";

//webPage += "<h3>Modulo Sol</h3>";

//webPage += "<p><a href=\"Reg3_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_3</button></a>&nbsp;<a href=\"Reg2_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_2</button></a>&nbsp;<a href=\"Reg1_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_1</button></a>&nbsp;<a href=\"Inc_IZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Inc</button></a>&nbsp;<a href=\"Inc_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Inc</button></a>&nbsp;<a href=\"Reg1_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_1</button></a>&nbsp;<a href=\"Reg2_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_2</button></a>&nbsp;<a href=\"Reg3_DER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Re_3</button></a></p>";

webPage += "<table align=\"center\"><thead>"; 
webPage += "  <tr>"; 
webPage += "    <th colspan=\"5\">Panel Izquierda</th>"; 
webPage += "    <th colspan=\"5\">Panel Centro</th>"; 
webPage += "    <th colspan=\"5\">Panel Derecha</th>"; 
webPage += "  </tr></thead>"; 
webPage += "<tbody>"; 
webPage += "  <tr>"; 
webPage += "    <td><h3>&theta;</h3></td>"; 
webPage += "    <td><a href=\"movHnegIZQ1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHnegIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposIZQ1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><h3>&theta;</h3></td>"; 
webPage += "    <td><a href=\"movHnegCEN1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHnegCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposCEN1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><h3>&theta;</h3></td>"; 
webPage += "    <td><a href=\"movHnegDER1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHnegDER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposDER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movHposDER1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "  </tr>"; 
webPage += "  <tr>"; 
webPage += "    <td><h3>&phi;</h3></td>"; 
webPage += "    <td><a href=\"movVnegIZQ1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVnegIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposIZQ1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><h3>&phi;</h3></td>"; 
webPage += "    <td><a href=\"movVnegCEN1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVnegCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposCEN1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><h3>&phi;</h3></h3></td>"; 
webPage += "    <td><a href=\"movVnegDER1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&lArr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVnegDER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&larr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposDER\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rarr;</h3></button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"movVposDER1\"><button style=\"font-size: 20px; padding: 10px 20px;\"><h3>&rArr;</h3></button></a>&nbsp;</td>"; 
webPage += "  </tr>"; 
webPage += "  <tr>"; 
webPage += "    <td colspan=\"3\"><a href=\"testingIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Prueba</button></a>&nbsp;</td>"; 
webPage += "    <td colspan=\"2\"><a href=\"AutoIZQ\"><button style=\"font-size: 20px; padding: 10px 20px;\">Automatico</button></a>&nbsp;</td>"; 
webPage += "    <td colspan=\"3\"><a href=\"testingCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\">Prueba</button></a>&nbsp;</td>"; 
webPage += "    <td colspan=\"2\"><a href=\"AutoCEN\"><button style=\"font-size: 20px; padding: 10px 20px;\">Automatico</button></a>&nbsp;</td>"; 
webPage += "<td colspan=\"3\"><a href=\"testingDER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Prueba</button></a>&nbsp;</td>"; 
webPage += "    <td colspan=\"2\"><a href=\"AutoDER\"><button style=\"font-size: 20px; padding: 10px 20px;\">Automatico</button></a>&nbsp;</td>"; 
webPage += "  </tr>"; 
webPage += "</tbody></table>"; 

/*
webPage += "<h3>Acciones Combinadas</h3>";

webPage += "<p><a href=\"AutoPaneles\"><button style=\"font-size: 20px; padding: 10px 20px;\">AutoPaneles</button></a>&nbsp;<a href=\"PruebaTotal\"><button style=\"font-size: 20px; padding: 10px 20px;\">PruebaTotal</button></a></p>";
*/

webPage += "<table align=\"center\"><thead>"; 
webPage += "  <tr>"; 
webPage += "    <th><h4>ESP8266 Info</h4></th>"; 
webPage += "    <th><h4>Elaborado por: Pablo Vivar Colina</h4></th>"; 
webPage += "  </tr></thead>"; 
webPage += "<tbody>"; 
webPage += "  <tr>"; 
webPage += "    <td><p>Chip Flash Speed:"; 
webPage += ESP.getFlashChipSpeed()/1000000;
webPage += " [MHz]__</p></td>";
webPage += "    <td>www.idea161.org</td>"; 
webPage += "  </tr>"; 
webPage += "  <tr>"; 
webPage += "    <td><p>Chip Work Speed:"; 
webPage += ESP.getCpuFreqMHz();
webPage += " [MHz]__</p> </td>";
webPage += "    <td>github.com/pablovi33/HelioPanel</td>"; 
webPage += "  </tr>"; 
webPage += "</tbody></table>"; 

/*
webPage += "<table><thead>"; 
//webPage += "  <tr>"; 
//webPage += "    <th colspan=\"6\"><h4>Acciones Combinadas</h4></th>"; 
//webPage += "  </tr></thead>"; 
webPage += "<tbody>"; 
webPage += "  <tr>"; 
webPage += "    <td><a href=\"AutoPanel_1\"><button style=\"font-size: 20px; padding: 10px 20px;\">AutoPanel_1</button></a>&nbsp;<br></td>"; 
webPage += "    <td><a href=\"AutoPanel_2\"><button style=\"font-size: 20px; padding: 10px 20px;\">AutoPanel_2</button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"AutoPanel_3\"><button style=\"font-size: 20px; padding: 10px 20px;\">AutoPanel_3</button></a>&nbsp;</td>"; 
webPage += "    <td><a href=\"Total_1\"><button style=\"font-size: 20px; padding: 10px 20px;\">Total_1</button></a></td>"; 
webPage += "    <td><a href=\"Total_2\"><button style=\"font-size: 20px; padding: 10px 20px;\">Total_2</button></a></td>"; 
webPage += "    <td><a href=\"Total_3\"><button style=\"font-size: 20px; padding: 10px 20px;\">Total_3</button></a></td>"; 
webPage += "  </tr>"; 
webPage += "</tbody>"; 
webPage += "</table>";
*/



//webPage += "<h4>ESP8266 Info</h4>";

//   webPage += "<p>Chip ID: ";  
//  webPage += ESP.getFlashChipId();   1458415
//  webPage += "</p>";
//  webPage += "<p>Core Version: ";
//  webPage += ESP.getCoreVersion();   3.1.2
//  webPage += "</p>";
//  webPage += "<p>Chip Real Size: ";
//  webPage += ESP.getFlashChipRealSize()/1024;   4096 Kbit
//  webPage += " Kbit</p>";
//  webPage += "<p>Chip Size: ";
//  webPage += ESP.getFlashChipSize()/1024;   1024 Kbit
//  webPage += " Kbit</p>";
  
  //webPage += "<p>Chip Flash Speed: ";
  //webPage += ESP.getFlashChipSpeed()/1000000;
  //webPage += " MHz</p>";
  //webPage += "<p>Chip Work Speed: ";
  //webPage += ESP.getCpuFreqMHz();
  //webPage += " MHz</p>";
//  webPage += "<p>Chip Mode: ";   0
//  webPage += ESP.getFlashChipMode();
//  webPage += "</p>";

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

   /*server.on("/AutoPaneles", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[APAN]");

    //delay(1000);
    delay(10);
  });*/

 /*server.on("/PruebaTotal", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[ATOT]");

    //delay(1000);
    delay(10);
  });*/


 server.on("/AutoPanel", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[AUP0]");

    //delay(1000);
    delay(10);
  });

 server.on("/AutoPanel_1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[AUP1]");

    //delay(1000);
    delay(10);
  });

  
 server.on("/AutoPanel_2", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[AUP2]");

    //delay(1000);
    delay(10);
  });


  
 server.on("/AutoPanel_3", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[AUP3]");

    //delay(1000);
    delay(10);
  });

server.on("/Total", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TOT0]");

    //delay(1000);
    delay(10);
  });

  
 server.on("/Total_1", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TOT1]");

    //delay(1000);
    delay(10);
  });

 server.on("/Total_2", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TOT2]");

    //delay(1000);
    delay(10);
  });

 server.on("/Total_3", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led_pin, LOW);
    //banderaB_0=false;
    Serial.println("[TOT3]");

    //delay(1000);
    delay(10);
  });

  server.begin();
  Serial.println("HTTP server started");
  
}
     
 void loop(void){
 server.handleClient();

}
