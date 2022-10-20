#include <SoftwareSerial.h>
const int leftF = 5;
const int leftB = 4;
const int rightF = 6;
const int leftSense = A0;
const int rightSense = A1;
void setup() {
  // put your setup code here, to run once:
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
Serial.print(lightLeft);
Serial.print("     ");
Serial.print(lightRight);
Serial.print("     ");

 digitalWrite(leftF, HIGH);
     digitalWrite(rightF, HIGH);
int lightMid = analogRead(A2);

Serial.print(lightMid);
Serial.println();


if(lightLeft>100){
 
  digitalWrite(leftF, LOW);

 while(lightRight<100){
  lightLeft = analogRead(leftSense);
lightRight = analogRead(rightSense);
delay(10);
 }
}


else if(lightRight>100){
  digitalWrite(rightF, LOW);
   while(lightLeft<100){
  lightLeft = analogRead(leftSense);
lightRight = analogRead(rightSense);
delay(10);
 }
}

//else if(lightRight<100 and lightLeft<100){
  
//}

}
