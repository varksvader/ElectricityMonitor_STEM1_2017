/*
 * Filename: CurrentReader1
 * For Prototype1
 * By Varnika Sinha
 * November 26, 2016
 * 
 * This program reads current from the split core sensor and displays on the serial monitor. It also calculates the power based on the measured current and voltage. In this 
 * program, voltage is a constant so prototyping can be more focused on meauring current. 
 */

//Include Wire I2C Library
#include <Wire.h>
int address = A0; // I2C address
double voltage = 120; // var voltage as a constant
double tkWh = 0; //var for total kiloWatt hour
double tWh = 0; //var for total Watt hour
void setup() 
{
  Serial.begin(9600);  // Create Serial Object (9600 Baud)
  Wire.begin();
}

void loop() 
{
  Wire.beginTransmission(address); // Start communication
  /*Wire.write(146); // Command header 
  Wire.write(106); // Command header 
  Wire.write(1);  // Command 1
  Wire.write(1);  // Start Channel no 
  Wire.write(1);  // End Channel no 
  Wire.write(0); */
  Wire.write(0); 
  Wire.write(0 & 255); // CheckSum
  //Wire.endTransmission(); // Complete Transmission
  Wire.requestFrom(address, 5); 
  unsigned long MSB1 = Wire.read();
  MSB1= MSB1*65536;
  unsigned long MSB = Wire.read();
  MSB=MSB*256;
  unsigned long LSB = Wire.read();
  MSB1=MSB1+MSB+LSB;
  double current = ((double)MSB1)/(double)1000;  
   
  Serial.print(current,3); //// current on ch 1
  Serial.print(",");    
  double Power = voltage * current; /// power on ch1
  Serial.print(Power,3);
  Serial.print(",");    
  double Wh = 0.000833 * Power; /// Watt hour on ch1
  Serial.print(Wh,4);
  Serial.print(",");
  tWh = tWh + Wh; /// total watt hour used 
  Serial.print(tWh,4);
  Serial.print(",");
  tkWh = tWh/1000; /// total kilo watt hour used 
  Serial.print(tkWh,4);
  Serial.print("\n");
  
  //Wire.endTransmission(); // Complete Transmission
  
  delay(3000);
}
