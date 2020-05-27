#include <Servo.h>
   
Servo rotateServo; // servo object to aim the spray
Servo shootServo; // servo object to shoot the spray
int val; // variable to read the value from the analog pin
const int ledPin = 13; // where the led pin is located
const int buttonPin = 12; // where button to be pressed and switch modes is located
int buttonState = 0;
int potPort = 0; // port connecting to potentiometeter
int pos = 0;

// Initializing buzzer locations
const int buzzer = 9;
const int buzzerButton = 8;
int buzzerState = 0;


void setup() {
   rotateServo.attach(10);
   shootServo.attach(11);
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);

   pinMode(buzzer, OUTPUT); // setup for buzzer
}

// need a signal first from server still. This program is in preparation.

void loop() {
  /*
   * Manual Mode
   * In case of Emergency, this mode will let the user activate the spray
   * under their direct control. Rotate and shoot. Manual mode should always
   * be available to control. Higher level importance than server instructions.
   */
   buttonState = digitalRead(buttonPin);  // read button state for spraying
   buzzerState = digitalRead(buzzerButton); // read button state for buzzer
   // Automatically move servo to shoot the spray
   if (buttonState == HIGH) { // button press
    digitalWrite(ledPin, HIGH); // turn LED on
    tone(buzzer, 1000); // send 1KHz sound signal constantly (while shooting)
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 to 120 degrees
    rotateServo.write(pos); // lets servo know what position to be in
    delay(15); // wait 15 ms for servo
    }
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 120 to 0 degrees
      rotateServo.write(pos);
      delay(15);
    }
    noTone(buzzer);
   }
  // Manually rotate servo to aim at target direction
  digitalWrite(ledPin, LOW); // keep LED off
  val = analogRead(potPort); // read potentiometer value (0 to 1023)
  val = map(val, 0, 1023, 0, 90); // Re-map val to servo (0 to 90)
  shootServo.write(val); // set servo position based off val
  // buzzer goes off when target comes closer
  if (buzzerState == HIGH) {
    tone(buzzer, 1000);
    delay(800);
    noTone(buzzer);
    delay(800);
  }
   delay(15);

  int signal = 3;
  /*
   * Danger Level: 1
   * No reaction.
   */
  if (signal == 1){
    noTone(buzzer);
  }
  /*
   * Danger Level: 2
   * Unmasked person detected. Slow warning.
   */
  if (signal == 2){
    tone(buzzer, 800);
    delay(1000);
    noTone(buzzer);
    delay(1000);
  }
  /*
   * Danger Level: 3
   * Emergency Warning. Short pattern to alert user and surroundings.
   */
  if (signal == 3){
    tone(buzzer, 700);
    delay(600);
    tone(buzzer, 500);
    delay(600);
  }
  /*
   * Danger Level: 4
   * Activation Mode. Buzzer will go off continuously during spray.
   */
  if (signal == 4){
    tone(buzzer, 1000);
  }
}
