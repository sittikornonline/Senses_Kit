#include "Senses_wifi_esp32.h"
#include <Adafruit_NeoPixel.h>
int button_pin  = 26;
int led_pin     = 27;
int numPixels   = 1;
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel *pixels;
String response = "";
const char *ssid    = "your-wifi-network-name";
const char *passw   = "your-wifi-password";
const char *userid  = "your-senses-user-id";
const char *key     = "your-device-key";

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

  int state_button = digitalRead(button_pin);

  if ( state_button == 0)
  {
    pixels->setPixelColor(0, pixels->Color(255, 0, 0));  pixels->show(); delay(500);
    pixels->setPixelColor(0, pixels->Color(0, 255, 0));  pixels->show(); delay(500);
    pixels->setPixelColor(0, pixels->Color(0, 0, 255));  pixels->show(); delay(500);

    response = myiot.send(1, state_button);
    Serial.println(response);
  }

  else  if (state_button == 1)
  {
    pixels->clear();
    pixels->show();
    response = myiot.send(1, state_button);
    Serial.println(response);
  }
  delay(1000);
}
