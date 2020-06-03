
/*------------------------------------------------------------------------------------------
/--Programmer: Edward Dickhoff
/--Team 2, CS176j
/--
/--Overview: This is an arduino nano module that will utilize an ultrasonic sensor to
/-- get the distance of a target. This base module simple takes in data from the ultrasonic
/-- and sends one of three output signals:
/--   1: no objects within 6ft
/--   2: Object between 3 and 6 feet
/--   3: Object between 0 and 3 feet
-------------------------------------------------------------------------------------------*/
  
  // variable declaring the led inputs and ultrasonic triger and echo pins
  // along with the temperary variables
int signal1 = 4;
int signal2 = 5;
long trig=8;
long echo=9;
long data_in;
long dist;

void setup() {
      //declaring 
  pinMode(signal1,OUTPUT);
  pinMode(signal2,OUTPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop() {
    //Get ultra sonic distance measurments 
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  data_in = pulseIn(echo,HIGH);
  dist=data_in*0.017;
    
    //output to serial monitor for debugging
  Serial.print("Distance in cm:   ");
  Serial.println(dist);
  
  
  
  if(dist>160)
  {
      //if the distance is greater thatn 160cm turn off the output signals
    digitalWrite(signal1,LOW); 
    digitalWrite(signal2,LOW); 
  }
  
  if(dist>94)
  {
      //if the object is within 6 feet turn on the first signal
    digitalWrite(signal1,HIGH); 
  }
  
  if(dist>15)
  {
      //if the object is with in 3 feet turn on the second signal
    digitalWrite(signal2,HIGH); 
  }
    
}