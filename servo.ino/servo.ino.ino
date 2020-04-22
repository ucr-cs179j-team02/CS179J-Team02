#include <Servo.h>
   
Servo myservo; // servo object to control servo
int val; // variable to read the value from the analog pin
const int buttonPin = 12; // where button to be pressed and switch modes is located
int buttonState = 0;//LOW;//0;
const int ledPin = 13; // where the led pin is located
int potPort = 1; // port connecting to potentiometeter

void setup() {
  // Serial.begin(9600);
   myservo.attach(9);
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
}


/*
 * For Milestone 1 demo:
 * Button to swap between manual mode and "input" mode.
 * LED will light up during "input" mode.
 * "input" mode will be set to 1 for demo. It is supposed to take in info from the servers.
 */

void loop() {
//   mode = analogRead(
   // manual mode:
   buttonState = digitalRead(buttonPin);  // know the state if button is being pressed
   
   //Serial.println(buttonState);

   if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
   }
   else {
    digitalWrite(ledPin, LOW);
   }
   val = analogRead(potPort);
   // reads the value of the potentiometer (value between 0 and 1023)
   val = map(val, 0, 1023, 0, 180);
   // scale it to use it with the servo (value between 0 and 180)
   
   myservo.write(val); // sets the servo position according to the scaled value
   delay(15);
}
