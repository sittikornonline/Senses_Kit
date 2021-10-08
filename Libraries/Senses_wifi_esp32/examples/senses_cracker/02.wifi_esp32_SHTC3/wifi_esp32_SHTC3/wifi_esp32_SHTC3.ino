#include "Senses_wifi_esp32.h"
#include "Adafruit_SHTC3.h"

const char *ssid    = "your-wifi-network-name";
const char *passw   = "your-wifi-password";
const char *userid  = "your-senses-user-id";
const char *key     = "your-device-key";

String response;
float t, h;

Senses_wifi_esp32 myiot;
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

void setup() {
  Serial.begin(115200);
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
  if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");
}

void loop() {

  response = "";

  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);

  t = temp.temperature;
  h = humidity.relative_humidity;

  Serial.println("Temperature is " + String(t) + " celcuis");
  Serial.println("Humidity is " + String(h) + " %RH");
  Serial.println("----------------------------------------");

  response = myiot.send(1, t);
  Serial.println(response);

  response = myiot.send(2, h);
  Serial.println(response);

  delay(5000);
}
