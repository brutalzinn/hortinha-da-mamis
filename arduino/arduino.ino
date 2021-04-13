#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial linkEsp(7, 6); // RX, TX
#define LAMP 12
 char inData = "";
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  linkEsp.begin(115200);
  pinMode(LAMP, OUTPUT);
   digitalWrite(LAMP, LOW);
Serial.println("Started hortinha system. Waiting alexa calls.. by esp 8266");
}

void loop() {
  // put your main code here, to run repeatedly:
    while  (linkEsp.read() >= 0) 
  { 
              StaticJsonDocument<300> doc;
    DeserializationError err = deserializeJson(doc, linkEsp);

     if (err) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(err.f_str());
    return;
  }
int hortinha = doc["HORTA"];
   Serial.print(hortinha);
    } 
  
   //  linkEsp.read(); 
     
      
  
     

}
