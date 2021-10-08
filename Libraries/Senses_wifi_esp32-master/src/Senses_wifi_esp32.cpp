#include "Senses_wifi_esp32.h"

#define SENSES_HOST "www.sensesiot.com"
#define SENSES_PORT 4000
#define retry_wait 1000
#define LAGTIME 100

#define TONY_POWER_PIN 2

String Senses_wifi_esp32::connect(const char *ssid, const char *passw, const char *userid, const char *key){

  _ssid = ssid;
  _passw = passw;
  _userid = userid;
  _key = key;

  WiFi.begin(_ssid,_passw);
  Serial.print("SENSES platform start connecting.");

  while (WiFi.status() != WL_CONNECTED){
    delay(retry_wait);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED){

    /* Connect to SENSES server */
    WiFiClient client;
    if(client.connect(SENSES_HOST, SENSES_PORT)){
      _path = "GET /";
      _path += " HTTP/1.1\r\n";
      _path += "Host: ";
      _path += SENSES_HOST;
      _path += ":";
      _path += SENSES_PORT;
      _path += "\r\n";
      _path += "Connection: keep-alive\r\n\r\n";

      client.print(_path);
      delay(LAGTIME);

      while(client.available()){
        _response = client.readStringUntil('\r');
      }

      return _response;

    }
  }

}

String Senses_wifi_esp32::send(int slotnum, float data){

  _slotnum = slotnum;
  _data = data;

  WiFiClient client;
  if(client.connect(SENSES_HOST, SENSES_PORT)){

    _path = "GET /send/";
    _path += String(_userid);
    _path += "/";
    _path += String(_key);
    _path += "/";
    _path += String(_slotnum);
    _path += "/";
    _path += String(_data);

    _path += " HTTP/1.1\r\n";
    _path += "Host: ";
    _path += SENSES_HOST;
    _path += ":";
    _path += SENSES_PORT;
    _path += "\r\n";
    _path += "Connection: keep-alive\r\n\r\n";

    client.print(_path);
    delay(LAGTIME);

    while(client.available()){
      _response = client.readStringUntil('\r');
    }

    return _response;

  }

}

void Senses_wifi_esp32::setPowerOff(){
  pinMode(TONY_POWER_PIN, OUTPUT);
  digitalWrite(TONY_POWER_PIN, LOW);
}

void Senses_wifi_esp32::setPowerOn(){
  pinMode(TONY_POWER_PIN, OUTPUT);
  digitalWrite(TONY_POWER_PIN, HIGH);
}
