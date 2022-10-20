
#include <SoftwareSerial.h>


const int m1 = 4;
const int m2 = 5;
const int m3 = 6;
const int m4 = 7;

const int trigPin = 3;
const int echoPin = 2;



void setup() {
  // put your setup code here, to run once:
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  
delay(8000);
}

void loop() {
  // put your main code here, to run repeatedly:
if (getUltraSonic() <= 20) 
{
 digitalWrite(m4, LOW);
digitalWrite(m3, LOW);
digitalWrite(m2, LOW);
digitalWrite(m1, LOW); 
  }
  else 
  {
    digitalWrite(m4, HIGH);
digitalWrite(m3, HIGH);
digitalWrite(m2, HIGH);
digitalWrite(m1, HIGH);
  }
}


int getUltraSonic(){
  long duration; // variable for the duration of sound wave travel
int distance;
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  
  return distance;
}
