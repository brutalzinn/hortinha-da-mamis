#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial linkEsp(7, 6); // RX, TX
#define LAMP 12
 char inData = "";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  linkEsp.begin(9600);
  pinMode(LAMP, OUTPUT);
   digitalWrite(LAMP, LOW);
Serial.println("Started hortinha system. Waiting alexa calls.. by esp 8266");
}

void loop() {
  // put your main code here, to run repeatedly:
while(linkEsp.available()) {

   
              StaticJsonDocument<300> doc;
    DeserializationError err = deserializeJson(doc, linkEsp);

     if (err) {
  //  Serial.print(F("deserializeJson() failed: "));
//    Serial.println(err.f_str());
     Serial.flush();
    return;
  }
String hortinha = doc["HORTA"];
if(hortinha == "ON"){
   digitalWrite(LAMP, LOW);
}else if(hortinha == "OFF"){
    digitalWrite(LAMP, HIGH);
}
   Serial.println(hortinha);
   Serial.flush();
    
  
   //  linkEsp.read(); 
     
      
  
} 

}
