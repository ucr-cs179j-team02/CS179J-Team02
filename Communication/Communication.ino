void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  // Arduino's on-board LED
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    switch(Serial.read()) {
      case '0': digitalWrite(13,LOW);
                break;
      case '1': digitalWrite(13,HIGH);
                break;
      default:  break;
    }
  }
}

/*
 * Shell Script on Python:
 * import serial
 * ser = serial.Serial('COM3', 9600)
 * while 1:
 *    val = input("Enter 0 or 1 to control LED:");
 *    ser.write(val.encode())
 *    # 0 turns LED off. 1 turns LED on.
 */
