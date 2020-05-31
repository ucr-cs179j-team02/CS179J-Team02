
#include "FastLED.h"

//#define LED_PIN 4
#define DATA_PIN    4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    10
#define BRIGHTNESS  60
CRGB leds[NUM_LEDS];
int signal = 0;

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "DD";
const char* password = "Lunalanai@1";
 
ESP8266WebServer server(80);

void handleNotFound(){
  server.send(200, "", "");
  signal = 1;
  off();
}

void handleRequestOff(){
    signal = 1;
    server.send(200, "", "");
    off();
}

void handleRequestBelt1(){
    signal = 2;
    server.send(200, "", "");
    belt1();
}
void handleRequestBelt2(){
    signal = 3;
    server.send(200, "", "");
    belt2();
}

void handleRequestBelt3(){
    signal = 4;
    server.send(200, "", "");
    belt3();
}

void off(){
  for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(0,0,0);
      FastLED.show();
    }
    delay(250);
}

void belt1(){
  for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,0,0); // red
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(170,0,255);  // purple
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(0,0,255);  // blue
      FastLED.show();
      delay(50);
    }
    for (int i = 9; i >= 0; i--) {
      leds[i] = CRGB(255,0,170);  // magenta
      FastLED.show();
      delay(50);
    }
}
void belt2(){
  server.send(200, "", "");
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,0,0);
      FastLED.show();
    }
    delay(250);
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(0,0,0);
      FastLED.show();
    }
    delay(250);
}
void belt3(){
  for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,255,255);  // white
      FastLED.show();
  }
}

void setup() {
  Serial.begin(115200);
  
  delay(1500); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Server IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/off", handleRequestOff);
  server.on("/belt1", handleRequestBelt1);
  server.on("/belt2", handleRequestBelt2);
  server.on("/belt3", handleRequestBelt3);

  
  server.onNotFound(handleNotFound);
  server.begin();
  
  Serial.println("Server listening");
}
 
void loop() {
  server.handleClient();

    if (signal == 1) {
    FastLED.clear(0);
  }
  /*
   * Danger Level: 2
   * Light show to grab surrounding persons' attention.
   * Indicate that something is happening.
   */
  else if (signal == 2) {
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,0,0); // red
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(170,0,255);  // purple
      FastLED.show();
      delay(50);
    }
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(0,0,255);  // blue
      FastLED.show();
      delay(50);
    }
    for (int i = 9; i >= 0; i--) {
      leds[i] = CRGB(255,0,170);  // magenta
      FastLED.show();
      delay(50);
    }
  }
  /*
   * Danger Level: 3
   * Emergency Warning. Lights will flash red continuously.
   */
  else if (signal == 3) {
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,0,0);
      FastLED.show();
    }
    delay(250);
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(0,0,0);
      FastLED.show();
    }
    delay(250);
  }
  /*
   * Danger Level: 4
   * Activation Mode. Red will stay on.
   */
  else if (signal == 4) {
    for (int i = 0; i < 10; i++) {
      leds[i] = CRGB(255,0,0);  // red
      FastLED.show();
    }
  }

}

