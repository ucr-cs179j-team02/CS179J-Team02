#include <FastLED.h>

#define LED_PIN 7
#define NUM_LEDS 10

CRGB leds(NUM_LEDS);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // temp signal value
  int signal = 1;
  /*
   * Danger Level: 1
   * No reaction
   */
  if (signal == 1) {
    FastLED.clear(0)
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
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255,0,0);
      FastLED.show();
    }
    delay(500);
    FastLED.clear();
    delay(300);
  }
  /*
   * Danger Level: 4
   * Activation Mode. Lights will stay on.
   */
  else if (signal == 4) {
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255,255,255);  // white
      FastLED.show();
    }
  }
}
