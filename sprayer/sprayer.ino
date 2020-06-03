#include <Servo.h>
   
Servo rotateServo; // servo object to aim the spray
Servo shootServo; // servo object to shoot the spray
int val = 0; // variable for rotating large servo (angle set to center)
const int buttonPin = 12; // where button to be pressed and switch modes is located
int buttonState = 0;
//int potPort = 0; // port= connecting to potentiometeter
int pos = 0; // variable for moving small servo (shoot)
// Initializing buzzer locations
const int buzzer = 9;
int signal_status;

void setup() {
   Serial.begin(9600);
   rotateServo.attach(11);
   shootServo.attach(10);
   pinMode(buttonPin, INPUT);
   pinMode(buzzer, OUTPUT);
}


void loop() {
  /*
   * Manual Mode. Initial State.
   * Manually pressing button will automatically send program to signal_status 4,
   * a state where sprayer is shooting.
   */
  // temp received signal_status value
  
  if (Serial.available()) {
      switch(Serial.read()) {
        case '1': signal_status = 1;
                  break;
        case '2': signal_status = 2;
                  break;
        case '3': signal_status = 3;
                  break;
        case '4': signal_status = 4;
                  break;
        case '5': signal_status = 5;
                  break;
        case '6': signal_status = 6;
                  break;
        default:  
          signal_status = 1;
          break;
      }
    
  }
    Serial.print(signal_status);
  /*
   * Shell Script on Python:
   * import serial
   * ser = serial.Serial('COM3', 9600)
   * while 1:
   *    val = input("Input Danger Level(1-4):")
   *    ser.write(val.encode())
   */
 
  noTone(buzzer);
  buttonState = digitalRead(buttonPin);  
  if (buttonState == HIGH) { // button press
    signal_status = 6;
}
  
  /*
   * Danger Level: 1
   * No reaction.
   */
  if (signal_status == 1){
    rotateServo.write(60);
    noTone(buzzer);
  }
  /*
   * Danger Level: 2
   * Unmasked person detected. 
   * Slow warning with buzzer.
   */
  if (signal_status == 2){
    tone(buzzer, 800);
    delay(1000);
    noTone(buzzer);
    delay(1000);
  }
  /*
   * Danger Level: 3
   * Emergency Warning. 
   * Short buzzer pattern to alert user and surroundings.
   * Spray will rotate to face unmasked target.
   */
  if (signal_status == 3) { // center
    
    rotateServo.write(60);
    tone(buzzer, 700);
    delay(600);
    tone(buzzer, 500);
    delay(600);
  }
  else if (signal_status == 4) { // left
    
    rotateServo.write(120);
    tone(buzzer, 700);
    delay(600);
    tone(buzzer, 500);
    delay(600);
  }
  else if (signal_status == 5) { // right
    rotateServo.write(0);
    tone(buzzer, 700);
    delay(600);
    tone(buzzer, 500);
    delay(600);
  }

  
  /*
   * Danger Level: 6
   * Activation Mode.
   * Buzzer will go off continuously.
   * Spray will go off.
   */
  if (signal_status == 6){
    tone(buzzer, 1000); // constant 1KHz sound status
    
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 to 120 degrees
    shootServo.write(pos); // lets servo know what position to be in
    delay(15); // wait 15 ms for servo
    }
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 120 to 0 degrees
      shootServo.write(pos);
      delay(15);
    }
  }
}
