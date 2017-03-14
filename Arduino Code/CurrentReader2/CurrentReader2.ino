/*
 * Filename: CurrentReader2
 * For Prototype1
 * By Varnika Sinha
 * December 3, 2016
 * 
 * This program measures the current using the voltage 
 */

#include "EmonLib.h" //Include EmonLib library
EnergyMonitor emon1; //Create an instance
 
void setup()
{  
  Serial.begin(9600);
  emon1.current(A0, 0.768);             // Current: input pin, calibration.
}
 
void loop()
{
  
  double Irms = emon1.calcIrms(3000);  // Calculate Irms only

  Serial.print((Irms)*120); // Apparent power
  Serial.print(" ");
  Serial.println(Irms);          // Irms

  
  
  //emon1.serialprint();
}
