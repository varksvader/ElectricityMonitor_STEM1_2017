#include <SPI.h>
#include <SD.h>

int chipSelect = 10;
boolean labels = true;

#include "EmonLib.h" /Include EmonLib library

EnergyMonitor emon1; // Create an instance of the Emonlib class

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  emon1.current(A0, 6.987); // Current: input pin, calibration.

  // Set up SD 
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  pinMode(10, OUTPUT);
}

void loop() {
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  double apparentPower = (Irms)*118.5;
  double current = Irms;
  
  Serial.print(apparentPower);
  Serial.print(" ");
  Serial.println(current);

  
  // put your main code here, to run repeatedly:
  //##############################
  // Lets log it to the card
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("180120_Datalog_Prototype2_WashingMachine.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    if (labels) {
      dataFile.print("Apparent Power");
      dataFile.print("         ");
      dataFile.println("Current");
      labels = false;
    }
    dataFile.print(apparentPower,5);
    dataFile.print(" W ");
    dataFile.print("           ");
    dataFile.print(current,5);
    dataFile.println(" A ");
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  
  delay(1000);
}
