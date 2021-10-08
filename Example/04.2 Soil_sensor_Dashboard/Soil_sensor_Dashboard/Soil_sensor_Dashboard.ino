#include "Senses_wifi_esp32.h"
const int analogInPin = 34;
int sensorValue = 0;
int outputValue = 0;

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = "";

int slot_soil = 1; 

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(9600);
   analogReadResolution(10);
  Serial.println("Senses Platfrom in WEIZEN");
  String response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 99);

  Serial.print("sensor = ");     Serial.print(sensorValue);
  Serial.print("\t output = ");  Serial.println(outputValue);

  String response = myiot.send(slot_soil, outputValue);
  Serial.println(response);

  delay(5000);
}
