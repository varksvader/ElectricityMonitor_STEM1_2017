const int vPin=A0; //sets pin to read voltage from to A0
double resistance=11.795;

void setup() 
{
  pinMode(vPin, INPUT); //set vPin as input to Board
  Serial.begin(9600); //sets up serial monitor to plot data values by 9600 baud
}

void loop() 
{
   double voltRead=analogRead(vPin); //sets var voltage to analog reading of pin AO
   double voltage=voltRead*120/1023;
   //double current=voltage/resistance;
   //double power=voltage*current;
   //double totpower+=power;
   Serial.println(voltage); //prints out values of var voltage in serial monitor
   //Serial.print("     ");
   //Serial.print(current);
   //Serial.print("     ");
   //Serial.println(power);
   //Serial.print("     ");
   //Serial.println(totpower);
}
