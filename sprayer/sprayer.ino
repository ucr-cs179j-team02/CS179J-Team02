#include <Servo.h>
   
Servo rotateServo; // servo object to aim the spray
Servo shootServo; // servo object to shoot the spray
int val; // variable for rotating large servo (angle)
const int buttonPin = 12; // where button to be pressed and switch modes is located
int buttonState = 0;
//int potPort = 0; // port connecting to potentiometeter
int pos = 0; // variable for moving small servo (shoot)

// Initializing buzzer locations
const int buzzer = 9;

void setup() {
   Serial.begin(9600);
   rotateServo.attach(10);
   shootServo.attach(11);
   pinMode(buttonPin, INPUT);
   pinMode(buzzer, OUTPUT);
}


void loop() {
  /*
   * Manual Mode. Initial State.
   * Manually pressing button will automatically send program to signal 4,
   * a state where sprayer is shooting.
   */
  // temp received signal value
  int signal = 1;
  if (Serial.available()) {
    switch(Serial.read()) {
      case '1': signal = 1;
                break;
      case '2': signal = 2;
                break;
      case '3': signal = 3;
                break;
      case '4': signal = 4;
                break;
      default:  break;
    }
  }
  /*
   * Shell Script on Python:
   * import serial
   * ser = serial.Serial('COM3', 9600)
   * while 1:
   *    val = input("Input Danger Level(1-4):");
   *    ser.write(val.encode())
   */
 
  noTone(buzzer);
  buttonState = digitalRead(buttonPin);  
  if (buttonState == HIGH) { // button press
    signal = 4;
}
  
  /*
   * Danger Level: 1
   * No reaction.
   */
  if (signal == 1){
    noTone(buzzer);
  }
  /*
   * Danger Level: 2
   * Unmasked person detected. 
   * Slow warning with buzzer.
   */
  if (signal == 2){
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
  if (signal == 3){
    tone(buzzer, 700);
    delay(600);
    tone(buzzer, 500);
    delay(600);
    /* val is set for now, 
     * but will really need to receive an actual value from server
     * to set the proper direction.
     * val = analogRead(potPort); // read potentiometer value (0 to 1023)
     * val = map(val, 0, 1023, 0, 90); // Re-map val to servo (0 to 90) based off data
     */
    val = 0; // center
//    val = 30; // to the left a bit
//    val = -30; // to the right a bit
    shootServo.write(val); // set servo position based off val
  }
  /*
   * Danger Level: 4
   * Activation Mode.
   * Buzzer will go off continuously.
   * Spray will go off.
   */
  if (signal == 4){
    tone(buzzer, 1000); // constant 1KHz sound signal
    
    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 to 120 degrees
    rotateServo.write(pos); // lets servo know what position to be in
    delay(15); // wait 15 ms for servo
    }
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 120 to 0 degrees
      rotateServo.write(pos);
      delay(15);
    }
  }
}
