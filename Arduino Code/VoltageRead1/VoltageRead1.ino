/*
 * Filename: VoltageRead1
 * For Prototype1
 * By Varnika Sinha
 * November 24, 2016
 * 
 * This program reads the voltage fluctuations through the split core current transducer to give an accurate reading of voltage to the user.
 * This reading is printed through the serial monitor, which can be opened by Tools>Serial Monitor or Tools>Serial Plotter.
 */
const int vPin=A0; //sets pin to read voltage from to A0
int voltage=0; //intializes var voltage

void setup() 
{
  pinMode(vPin, INPUT); //set vPin as input to Board
  Serial.begin(9600); //sets up serial monitor to plot data values by 9600 baud
}

void loop() 
{
   voltage=analogRead(vPin); //sets var voltage to analog reading of pin AO
   //voltage=voltage*120/1023;
   Serial.println(voltage); //prints out values of var voltage in serial monitor
}


