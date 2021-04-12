#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial linkEsp(7, 6); // RX, TX

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  linkEsp.begin(115200);
Serial.println("Started hortinha system. Waiting alexa calls.. by esp 8266");
}

void loop() {
  // put your main code here, to run repeatedly:
    StaticJsonDocument<200> doc;
 DeserializationError err = deserializeJson(doc, linkEsp);
  if (err) {
    return;
  }
    
      Serial.print("Hortinha Status=");
      bool hortaStatus = doc["HORTA"];
     if(hortaStatus){
      Serial.println("Ligado");
     }else{
       Serial.println("Desligado");
     }

    
    
      // Flush all bytes in the "link" serial port buffer
      while (linkEsp.available() > 0){
        linkEsp.read();
      }
    

}
