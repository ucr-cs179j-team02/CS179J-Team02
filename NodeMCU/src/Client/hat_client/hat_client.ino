#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() { 
  pinMode(D1, INPUT);
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("RonaZona_hat", "squidward420");                //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("connecting...");
  }
  delay(5000);
}
 
void loop() {
  if(WiFi.status() == WL_CONNECTED){                      //Check WiFi connection status
    WiFiClient client;
    HTTPClient http;                                      //Declare object of class HTTPClient
    if(digitalRead(D1) == HIGH){
      http.begin(client, "http://192.168.1.1:80/hat");
    }
    else{
      http.begin(client, "http://192.168.1.1:80/off");
    }
    http.GET();                            //Send the request
    http.end();
  }else{
    Serial.println("Error in WiFi connection");
    WiFi.reconnect();
    delay(5000);
  }
 delay(500);
}
