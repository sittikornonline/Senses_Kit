int sensor_pin  = 34;
int relay_pin   = 21;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  analogReadResolution(10);
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  
  sensorValue = analogRead(sensor_pin);
  Serial.print("sensorValue = ");     Serial.println(sensorValue);
  
  if (sensorValue < 500)
  {
    digitalWrite(relay_pin, HIGH);
  }
  else if (sensorValue > 500)
  {
    digitalWrite(relay_pin, LOW);
  }

  delay(1000);
}
