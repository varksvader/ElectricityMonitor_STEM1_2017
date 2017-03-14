int maxReading1 = 0;
int maxReading2 = 0;
int tempReading1 = 0;
int tempReading2 = 0;
long readingTime1 = 0;
int packetSent = 0;
long readingTime2 = 0;
long tempTime = 0;
void setup() {
Serial.begin(9600);
}
void loop() {
//if we are on a new packet, assign a new time value 
if(packetSent)
// max 64 characters
{
readingTime1 = millis(); 
//Serial.println(maxReading1); 
packetSent = 0;
maxReading1 = 0; maxReading2 = 0;
}
int i;
//Run for 20 samples to capture peak of voltage signal 
for(i=0;i<250;i++)
{
//Get ADC reading for both sensors
tempReading1 = analogRead(A0);
//tempReading2 = analogRead(1);
//if either reading larger than max value seen since //last transmission, set as new max value and record //time
//if(tempReading1 > maxReading1){ maxReading1 = tempReading1;
//}
if(tempReading2 > maxReading2){
maxReading2 = tempReading2; }
}
Serial.println(tempReading1); 
//Serial.println("/t"+maxReading2); 
}
