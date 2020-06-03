const int buzzer = 9;
const int buzzerButton = 8;
const int buttonPin = 12; // also makes buzzer at fastest speed
int buttonState = 0;
int buzzerState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  buzzerState = digitalRead(buzzerButton);
  if (buzzerState == HIGH) {
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec  
  }
  if (buttonState == HIGH) {
    tone(buzzer,1000);
  }
  
}
