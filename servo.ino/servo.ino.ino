#include <Servo.h>
   
Servo myservo; // servo object to control servo
int val; // variable to read the value from the analog pin
const int ledPin = 13; // where the led pin is located
const int buttonPin = 12; // where button to be pressed and switch modes is located
int buttonState = 0;
int potPort = 0; // port connecting to potentiometeter
int pos = 0;

void setup() {
   myservo.attach(11);
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
}


/*
 * For Milestone 1 demo:
 * Button to swap between manual mode and "input" mode.
 * LED will light up during "input" mode.
 * "input" mode will move servo so it can "shoot" in a 120 degree cone.
 * It is supposed to take in info from the servers.
 */

void loop() {
   buttonState = digitalRead(buttonPin);  // read button state
   // auto input mode
   if (buttonState == HIGH) { // button press
    digitalWrite(ledPin, HIGH); // turn LED on
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 to 120 degrees
    myservo.write(pos); // lets servo know what position to be in
    delay(15); // wait 15 ms for servo
    }
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 120 to 0 degrees
      myservo.write(pos);
      delay(15);
    }
   }
   // manual mode
   else {
    digitalWrite(ledPin, LOW); // keep LED off
    val = analogRead(potPort); // read potentiometer value (0 to 1023)
    val = map(val, 0, 1023, 0, 180); // Re-map val to servo (0 to 180)
    myservo.write(val); // set servo position based off val
   }
   delay(15);
}
