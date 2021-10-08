#include "Senses_wifi_esp32.h"
#include "MPU6050.h"
#include <Wire.h>

MPU6050 accelgyro;
Senses_wifi_esp32 myiot;

const char *ssid    = "your-wifi-network-name";
const char *passw   = "your-wifi-password";
const char *userid  = "your-senses-user-id";
const char *key     = "your-device-key";
String response = "";

int16_t ax, ay, az, gx, gy, gz;

void setup() {

  Serial.begin(115200);

  Wire.begin();
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? 
  "MPU6050 connection successful" : "MPU6050 connection failed");
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() 
{
  response = "";
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("a:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.println(az);

  response = myiot.send(1, ax);
  Serial.println(response);

  response = myiot.send(2, ay);
  Serial.println(response);

  response = myiot.send(3, az);
  Serial.println(response);

  delay(1000);
}
