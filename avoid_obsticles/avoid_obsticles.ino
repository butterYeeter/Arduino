const int trigPinL = 3;
const int echoPinL = 2;
const int trigPinR = 9;
const int echoPinR = 8;


#include <SoftwareSerial.h>
const int leftF = 5;
const int leftB = 4;
const int rightF = 6;
const int leftSense = A0;
const int rightSense = A1;
int threashHold = 20;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinR, INPUT);
pinMode(leftSense, INPUT);
pinMode(rightSense, INPUT);
Serial.begin(9600);
pinMode(13,OUTPUT);
digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
int lightLeft = analogRead(leftSense);
int lightRight = analogRead(rightSense);
Serial.print(getUltraSonicL());
Serial.print("     ");
Serial.print(getUltraSonicR());
Serial.print("     ");

 digitalWrite(leftF, HIGH);
     digitalWrite(rightF, HIGH);
int lightMid = analogRead(A2);

Serial.print(lightMid);
Serial.println();


if(getUltraSonicL()<threashHold and getUltraSonicR()<threashHold){
 if(getUltraSonicL()<getUltraSonicR()){
  digitalWrite(rightF, LOW);
 }else{
  digitalWrite(leftF, LOW);
 }
 
  
  Serial.println("State 1");


 
}
else if(getUltraSonicL()<threashHold){
  digitalWrite(rightF, LOW);
  
  Serial.println("State 2");
 
}
else if(getUltraSonicR()<threashHold){
  digitalWrite(leftF, LOW);
  
  Serial.println("State 3");
}else{
 digitalWrite(leftF, HIGH);
  digitalWrite(leftF, HIGH);
  
  Serial.println("State 4");
}
delay(100);

//else if(lightRight<100 and lightLeft<100){
  
//}

}

int getUltraSonicL(){
  long duration; // variable for the duration of sound wave travel
int distance;
digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  
  return distance;
}

int getUltraSonicR(){
  long duration; // variable for the duration of sound wave travel
int distance;
digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPinR, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  
  return distance;
}
