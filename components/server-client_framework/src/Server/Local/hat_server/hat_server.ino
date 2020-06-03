#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <AccelStepper.h>
#define IN1   D5   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN2   D6   // IN2 is connected to NodeMCU pin D2 (GPIO4)
#define IN3   D7   // IN3 is connected to NodeMCU pin D3 (GPIO0)
#define IN4   D8   // IN4 is connected to NodeMCU pin D4 (GPIO2)
#define MotorInterfaceType 8

const char *ssid = "RonaZona_hat";
const char *password = "squidward420";
 
ESP8266WebServer server(80);
AccelStepper stepper = AccelStepper(MotorInterfaceType, IN1, IN3, IN2, IN4);

void handleNotFound(){
    server.send(200, "", "");
    stepper.setSpeed(250);
}

void handleRequestFar(){
    server.send(200, "", "");
    stepper.setSpeed(250);
}

void handleRequestCloser(){
    server.send(200, "", "");
    stepper.setSpeed(500);
}

void handleRequestClose(){
    server.send(200, "", "");
    stepper.setSpeed(750);
}

void handleRequestVeryClose(){
    server.send(200, "", "");
    stepper.setSpeed(1000);
}
 
void setup() {
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

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/far", handleRequestFar);
  server.on("/closer", handleRequestCloser);
  server.on("/close", handleRequestClose);
  server.on("/veryclose", handleRequestVeryClose);
  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("Server listening");
  
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(250);
}
 
void loop() {
  server.handleClient();
  stepper.runSpeed();
}
