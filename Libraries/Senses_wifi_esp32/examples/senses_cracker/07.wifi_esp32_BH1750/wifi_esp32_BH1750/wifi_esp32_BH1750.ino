#include "Senses_wifi_esp32.h"
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;
Senses_wifi_esp32 myiot;

const char *ssid    = "your-wifi-network-name";
const char *passw   = "your-wifi-password";
const char *userid  = "your-senses-user-id";
const char *key     = "your-device-key";
String response = "";
void setup() {

  Serial.begin(115200);
  
  Wire.begin();
  lightMeter.begin();

  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {
  float lux = lightMeter.readLightLevel(); 
  Serial.print("Light: "); Serial.print(lux);  Serial.println(" lx");

  String response = myiot.send(1, lux);
  Serial.println(response);

  delay(5000);
}
