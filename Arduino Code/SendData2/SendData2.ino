/*
  Arduino & OpenEnergyMonitor 
  
  This sketch connects to an emoncms server and makes a request using
  Arduino Ethernet shield (or other based on Wiznet W5100) or an 
  Arduino Wifi Shield
  
  author Mirco Piccin aka pitusso
  
  based on 
  http://arduino.cc/en/Tutorial/WebClientRepeating
*/

#define WIFI

#include <SPI.h>

#include <WiFi.h>
#include <WiFiClient.h>


// Include Emon Library
#include "EmonLib.h"                   

//network configuration, WIRED or WIFI
  char ssid[] = "StayAway"; //  your network SSID (name) 
  char pass[] = "MW38!N96&B7G5S";    // your network password (use for WPA, or use as key for WEP)

  int status = WL_IDLE_STATUS;
  int keyIndex = 0;            // your network key Index number (needed only for WEP)
  
  WiFiClient client;


// Create an Emon instance
EnergyMonitor emon1;                   

//Emoncms configurations
char server[] = "emoncms.org";     // name address for emoncms.org
//IPAddress server(213, 138, 101, 177);  // numeric IP for emoncms.org (no DNS)

String apikey = "06d0149f45a8bb04ed57130b5bd677ea";  //api key
int node = 0; //if 0, not used

void setup() {
  // start serial port:
  Serial.begin(9600);

  // Display a welcome message
  Serial.println("Emoncms client starting...");

  emon1.current(A0, 0.668);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. 
    status = WiFi.begin(ssid, pass);
  } 
  Serial.println("Connected to wifi");
}

void loop() {
  
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting...");
    client.stop();
  }
  
  // if you're not connected, and at least <postingInterval> milliseconds have
  // passed sinceyour last connection, then connect again and
  // send data:
   
    //read sensors
    double Irms = emon1.calcIrms(3000);
    
    //Print values (debug)
    Serial.println(Irms);
    client.println(Irms*120);
      
    //send values
    //sendData();

}

// this method makes a HTTP connection to the server:
/*void sendData() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("Connecting...");
    // send the HTTP GET request:
    client.print("GET /api/post?apikey=");
    client.print(apikey);
    if (node > 0) {
      client.print("&node=");
      client.print(node);
    }
    client.print("&json={temp");
    client.print(":");
    client.print(tempValue + temp_offset);    
    client.print(",light:");
    client.print(lightValue);
    client.print(",power:");
    client.print(Irms*volt);   
    client.println("} HTTP/1.1");
    client.println("Host:emoncms.org");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();

    //client.print(Irms);

  } 
  else {
    // if you couldn't make a connection:
    Serial.println("Connection failed");
    Serial.println("Disconnecting...");
    client.stop();
  }
}*/
