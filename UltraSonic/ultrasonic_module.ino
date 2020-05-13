
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
int led1 =4;
int led2=5;
long trig=8;
long echo=9;
long Zeit;
long Strecke;//asdsa

void setup() {
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    Serial.begin(9600);
}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  data_in = pulseIn(echo,HIGH);
  dist=data_in*0.017;
  
  Serial.print("Distance in cm:   ");
  Serial.println(dist);
  
  
  
  if(Strecke>160)
  {
    digitalWrite(led1,LOW); 
    digitalWrite(led2,LOW); 
  }
  
  if(Strecke>94)
  {
    digitalWrite(led1,HIGH); 
  }
  
  if(Strecke>15)
  {
    digitalWrite(led2,HIGH); 
  }

    
}