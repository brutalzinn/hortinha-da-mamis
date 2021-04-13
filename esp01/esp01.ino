#include <Arduino.h>
#include <ESP8266WiFi.h>
#define RELAY_PIN_1 2
#include "fauxmoESP.h"
#include <ArduinoJson.h>

#define SERIAL_BAUDRATE 115200

#define WIFI_SSID "paes"
#define WIFI_PASS "garfield laranja"

#define LAMP_1 "HORTA"
fauxmoESP fauxmo;
void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(100);
  }
}
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  wifiSetup();
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);
  fauxmo.setPort(80); 

  fauxmo.enable(true);

  fauxmo.addDevice(LAMP_1);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    if ( (strcmp(device_name, LAMP_1) == 0) ) {

        if (state) {
           StaticJsonDocument<200> doc;
        doc["HORTA"] = 1;
        
          serializeJson(doc, Serial);
      } else {
         StaticJsonDocument<200> doc;
         doc["HORTA"] = 0;
           serializeJson(doc, Serial);
      }
   
    }
  });

}
void loop() {
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
  ESP.getFreeHeap();
  }
  
}
