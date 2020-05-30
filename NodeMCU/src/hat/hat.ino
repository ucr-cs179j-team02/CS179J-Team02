#include <Stepper.h>
 
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
#define IN1   D5   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN2   D6   // IN2 is connected to NodeMCU pin D2 (GPIO4)
#define IN3   D7   // IN3 is connected to NodeMCU pin D3 (GPIO0)
#define IN4   D8   // IN4 is connected to NodeMCU pin D4 (GPIO2)
 
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, IN1, IN2, IN3, IN4);
 
void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(115200);
}
 
void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1);
 
  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1);
}
