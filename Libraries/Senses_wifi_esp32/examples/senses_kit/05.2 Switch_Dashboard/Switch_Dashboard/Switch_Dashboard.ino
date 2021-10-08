#include "Senses_wifi_esp32.h"
const int sw1 = 32;
const int sw2 = 34;
const int sw3 = 26;
byte cnt = 0;

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = "";
Senses_wifi_esp32 myiot;
int slot_switch = 1; 

void setup() {
  Serial.begin(9600);

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);

  Serial.println("Senses Platfrom in WEIZEN");
  String response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop()
{
  int sw1Val = digitalRead(sw1);
  int sw2Val = digitalRead(sw2);
  int sw3Val = digitalRead(sw3);

  if (sw1Val == 0) {
    delay(200);
    cnt++;
    Serial.println(cnt);
  }
  else if (sw2Val == 0) {
    delay(200);
    cnt--;
    Serial.println(cnt);
  }
  else if (sw3Val == 0) {
    delay(200);
    cnt = 0;
    Serial.println(cnt);
  }
  String response = myiot.send(slot_switch, cnt);
  Serial.println(response);
}
