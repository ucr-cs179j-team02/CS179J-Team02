#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() { 
  pinMode(D5, OUTPUT);
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("RonaZona", "squidward420");                //WiFi connection
  delay(5000);
}
 
void loop() {
 if(WiFi.status() == WL_CONNECTED){                      //Check WiFi connection status
   HTTPClient http;                                      //Declare object of class HTTPClient
   HTTPClient httpHat;
   HTTPClient httpBelt;
   HTTPClient httpSpray;
   HTTPClient httpCamera;
   http.begin("http://192.168.1.1:80");
   httpHat.begin("http://192.168.1.1:80/hat");
   httpBelt.begin("http://192.168.1.1:80/belt");
   httpSpray.begin("http://192.168.1.1:80/spray");
   httpCamera.begin("http://192.168.1.1:80/camera");
   int httpCode = http.GET();                            //Send the request
   int httpCodeHat = http.GET();
   int httpCodeBelt = http.GET();
   int httpCodeSpray = http.GET();
   int httpCodeCamera = http.GET();
   if(httpCode == 201){
    digitalWrite(D5, LOW);
   }
   else if(httpCode == 202){
    digitalWrite(D5, HIGH);
   }
   Serial.println("----------");
   Serial.println(httpCode);
   Serial.println(httpCodeHat);
   Serial.println(httpCodeBelt);
   Serial.println(httpCodeSpray);
   Serial.println(httpCodeCamera);
   Serial.println("----------");
 }else{
    Serial.println("Error in WiFi connection");
    WiFi.reconnect();
    delay(5000);
 }
}
