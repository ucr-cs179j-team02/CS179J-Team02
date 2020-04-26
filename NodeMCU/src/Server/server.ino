#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
const char *ssid = "RonaZona";
const char *password = "squidward420";

bool activate = false;
 
ESP8266WebServer server(80);

void handleRequest(){
  if(activate){
    server.send(202, "", "");
  }
  else{
    server.send(201, "", "");
  }
}

void handleRequestHat(){
  if(activate){
    server.send(204, "", "");
  }
  else{
    server.send(203, "", "");
  }
}

void handleRequestBelt(){
  if(activate){
    server.send(206, "", "");
  }
  else{
    server.send(205, "", "");
  }
}

void handleRequestSpray(){
  if(activate){
    server.send(208, "", "");
  }
  else{
    server.send(207, "", "");
  }
}

void handleRequestCamera(){
  if(activate){
    server.send(210, "", "");
  }
  else{
    server.send(209, "", "");
  }
}
 
void setup() {
  pinMode(D2, INPUT);
  
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);

  IPAddress Ip(192, 168, 1, 1);
  IPAddress NMask(255, 255, 255, 0);

  WiFi.softAPConfig(Ip, Ip, NMask);
  
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());
  server.on("/", handleRequest);
  server.on("/hat", handleRequestHat);
  server.on("/belt", handleRequestBelt);
  server.on("/spray", handleRequestSpray);
  server.on("/camera", handleRequestCamera);
  server.begin();
 
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
  if(digitalRead(D2) == LOW){
    activate = false;
  }
  if(digitalRead(D2) == HIGH){
    activate = true;
  }
}
