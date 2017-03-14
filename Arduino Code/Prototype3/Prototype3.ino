double highest = 0;
int currentPin=A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double sensorValue = analogRead(currentPin);
  double current= abs((sensorValue-455)*710.9/1023+310)/10;
  delay(1000);

  double RMScurrent = current/sqrt(3);

  double power = (RMScurrent*255/1000);
  double kWh = (power*1/3600);
  double price = (kWh*21.80);
  double watt = current * 120;

  Serial.print(power);
  Serial.print("w ");
  Serial.print(current);
  Serial.print("a ");
  Serial.print(watt);
  Serial.println("p(w) ");
}
