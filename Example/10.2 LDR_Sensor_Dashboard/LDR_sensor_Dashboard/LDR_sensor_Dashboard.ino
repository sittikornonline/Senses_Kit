#include "Senses_wifi_esp32.h"
int sensor_pin  = 32;
int relay_pin   = 21;
int sensorValue = 0;

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = "";

int slot_sensor = 1;
int slot_relay  = 2;

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(9600);
  analogReadResolution(10);
  pinMode(relay_pin, OUTPUT);

  Serial.println("Senses Platfrom in WEIZEN");
  String response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {

  sensorValue = analogRead(sensor_pin);
  Serial.print("sensorValue = ");     Serial.println(sensorValue);

  if (sensorValue < 500)
  {
    digitalWrite(relay_pin, HIGH);
    myiot.send(slot_relay, 1);
  }
  else if (sensorValue > 500)
  {
    digitalWrite(relay_pin, LOW);
    myiot.send(slot_relay, 0);
  }

  String response = myiot.send(slot_sensor, sensorValue);
  Serial.println(response);

  delay(1000);
}
