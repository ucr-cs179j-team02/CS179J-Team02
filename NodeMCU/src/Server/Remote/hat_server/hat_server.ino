#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "---";
const char* password = "---";
 
ESP8266WebServer server(80);

void handleNotFound(){
  server.send(200, "", "");
}

void handleRequestOff(){
    server.send(200, "", "");
    digitalWrite(D4, LOW);
}

void handleRequestHat(){
    server.send(200, "", "");
    digitalWrite(D4, HIGH);
}
 
void setup() {
  Serial.begin(115200);
  
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/off", handleRequestOff);
  server.on("/hat", handleRequestHat);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();
}
