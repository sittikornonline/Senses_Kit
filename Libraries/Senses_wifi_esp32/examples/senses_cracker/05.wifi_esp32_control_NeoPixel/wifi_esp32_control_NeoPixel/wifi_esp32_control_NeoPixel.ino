#include "Senses_wifi_esp32.h"
#include <Adafruit_NeoPixel.h>
int button_pin  = 26;
int led_pin     = 27;
int numPixels   = 1;
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel *pixels;

const char *ssid    = "your-wifi-network-name";
const char *passw   = "your-wifi-password";
const char *userid  = "your-senses-user-id";
const char *key     = "your-device-key";
String response = "";
int control_port = 1;

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(115200);
  
  pixels = new Adafruit_NeoPixel(numPixels, led_pin, pixelFormat);
  pixels->begin();
  
  pinMode(button_pin, INPUT_PULLUP);
  
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {

  response = myiot.getDigitalControl(control_port);
  Serial.println(response);

  if (response == "on")
  {
    pixels->setPixelColor(0, pixels->Color(255, 0, 0));  pixels->show(); delay(500);
  }

  else if (response == "off")
  {
    pixels->clear();  pixels->show();
  }

  delay(1000);
}
