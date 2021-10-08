#include "Senses_wifi_esp32.h"
#define led_pin 13

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = ""; 

String response;
int control_port = 1;

Senses_wifi_esp32 myiot;

void setup(){
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop(){
  
  response = myiot.getDigitalControl(control_port);
  Serial.println(response);

    if(response=="on"){
      digitalWrite(led_pin, HIGH);
      }else{
        //..
     } 
  
    if(response=="off"){
      digitalWrite(led_pin, LOW);
      }else{
        //..  
     }

  delay(1000);
}
