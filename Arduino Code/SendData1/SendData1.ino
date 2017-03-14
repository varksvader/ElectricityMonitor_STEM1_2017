#include <SPI.h>
#include <Ethernet.h>

#include "EmonLib.h" //Include EmonLib library
EnergyMonitor emon1; //Create an instance

//Affectation d'une adresse MAC 
byte mac[] = {98, 01, A7, B0, D5, 11};

// Serveur avec Mysql
IPAddress server(192,168,1,10);

bool connected = false;

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() 
{
  Serial.begin(9600);
  emon1.current(A0, 0.668);  
  
  
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Impossible de configurer Ethernet en utilisant DHCP");  
      // Attente perpétuelle
      for(;;);
        }
    Serial.println("Configuration Ethernet DHCP : OK \n@IP : ");
      for (byte thisByte = 0; thisByte < 4; thisByte++)
      {
      // print the value of each byte of the IP address:
            Serial.print(Ethernet.localIP()[thisByte], DEC);
            Serial.println("."); 
       }
    delay(1000);
}

int val=0;

void loop()
{ 
  double Irms = emon1.calcIrms(3000);
        
        Serial.println(Irms);
        
      
          
  if (client.connect(server, 80)) 
  {
      Serial.println("\nconnected...");
      Serial.println("ARDUINO: forming HTTP request message");
      //client.println("POST /Test/PhpPost.php HTTP/1.1");
      //client.println("From: Arduino1 ");
      //client.println("User-Agent: HTTPTool/1.0");
      //client.println("Content-Type: application/x-www-form-urlencoded");
                //client.print("Content-Length:");
                //client.println(DatatoSend.length());
                client.println("Connection: close");
                client.println(Irms);
                //client.println();

      Serial.println("ARDUINO: HTTP message sent");
      delay(3000);
      if(client.available())
      {
        Serial.println("ARDUINO: HTTP message received");
        Serial.println("ARDUINO: printing received headers and script response...\n");
        
        while(client.available())
        {
          char c = client.read();
          Serial.print(c);
        }
      }
      else
      {
        Serial.println("ARDUINO: no response received / no response received in time");
      }
      
      //client.stop();
    }
    else
    {
      Serial.println("connection failure");
    }
    delay(2000);

}
