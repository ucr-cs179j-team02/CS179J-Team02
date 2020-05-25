#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "RonaZona_belt";
const char *password = "squidward420";
 
ESP8266WebServer server(80);

void handleNotFound(){
  server.send(200, "", "");
}

void handleRequestOff(){
    server.send(200, "", "");
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);
}

void handleRequestBelt(){
    server.send(200, "", "");
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
}

void handleRequestLights(){
    server.send(200, "", "");
    digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);
}

void handleRequestSpray(){
    server.send(200, "", "");
    digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);
}
 
void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  
  Serial.begin(115200);

  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
 
  WiFi.softAP(ssid, password);

  IPAddress Ip(192, 168, 1, 1);
  IPAddress NMask(255, 255, 255, 0);

  WiFi.softAPConfig(Ip, Ip, NMask);
  
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Server MAC address: ");
  Serial.println(WiFi.softAPmacAddress());

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/off", handleRequestOff);
  server.on("/belt", handleRequestBelt);
  server.on("/lights", handleRequestLights);
  server.on("/spray", handleRequestSpray);
  server.onNotFound(handleNotFound);
  
  server.begin();
 
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
}
