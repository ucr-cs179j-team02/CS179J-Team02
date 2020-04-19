#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() { 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("RonaZona", "squidward420");   //WiFi connection
  delay(5000);
}
 
void loop() {
 if(WiFi.status() == WL_CONNECTED){   //Check WiFi connection status
   HTTPClient http; //Declare object of class HTTPClient
   http.begin("http://192.168.1.1:80");
   int httpCode = http.GET(); //Send the request
   Serial.println(httpCode);
 }else{
    Serial.println("Error in WiFi connection");
    WiFi.reconnect();
    delay(5000);
 }
 delay(500);
}
