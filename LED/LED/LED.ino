const int ledPin1 = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin1, HIGH); // turn LED on
  delay(1000);
  digitalWrite(ledPin1, LOW); 
  delay(1000); 
  digitalWrite(ledPin2, HIGH); // turn LED on
  delay(1000);
  digitalWrite(ledPin2, LOW); 
  delay(1000); 
  digitalWrite(ledPin3, HIGH); // turn LED on
  delay(1000);
  digitalWrite(ledPin3, LOW); 
  delay(1000); 
}
