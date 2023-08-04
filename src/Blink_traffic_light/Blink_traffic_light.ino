#include <SoftwareSerial.h>

int blinkTime = 1000;
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 


void setup() {
  // put your setup code here, to run once:
pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
 
}

void loop() {
Serial.println(getUltraSonic());
delay(100);
  if(getUltraSonic()<20){
  // put your main code here, to run repeatedly:
  for (int i = 200; i>10; i=i-i/10){
digitalWrite(8, HIGH);
delay(i);
digitalWrite(8, LOW);

  digitalWrite(7, HIGH);
delay(i);
digitalWrite(7, LOW);

  digitalWrite(6, HIGH);
delay(i);
digitalWrite(6, LOW);
  }

  
  for (int i = 10; i<200; i=i+i/10){
digitalWrite(8, HIGH);
delay(i);
digitalWrite(8, LOW);

  digitalWrite(7, HIGH);
delay(i);
digitalWrite(7, LOW);

  digitalWrite(6, HIGH);
delay(i);
digitalWrite(6, LOW);
  }
if(blinkTime<10){
  blinkTime = 500;
}
blinkTime = blinkTime - blinkTime/10;
}}

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
