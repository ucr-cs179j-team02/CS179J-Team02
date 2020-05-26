const int ledPin1 = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

// need a signal first from server still. This program is in preparation.

void loop() {
  // temp signal value
  int signal = 4;
  /* 
   * Danger Level: 1
   * No reaction
   */
  if (signal == 1) {
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, LOW); 
    digitalWrite(ledPin3, LOW); 
  }
  
  /*
   * Danger Level: 2
   * Light show to grab threat's attention that there is a boundary.
   */
  else if (signal == 2) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin3, LOW);
    delay(600);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(600);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    delay(600);
  }

  /*
   * Danger Level: 3
   * Emergency Warning. Lights will flash continuously.
   */
  else if (signal == 3) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(200);
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin2, LOW); 
    digitalWrite(ledPin3, LOW); 
    delay(200);
  }

  /*
   * Danger Level: 4
   * Activation Mode. Lights will stay on.
   */
  else if (signal == 4) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  }
 
}
