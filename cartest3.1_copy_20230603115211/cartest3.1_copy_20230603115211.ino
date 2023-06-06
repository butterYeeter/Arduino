
//pins in use by the ultrasonic sensors
// 2 3  Forward
// 4 5  Right
// 6 7  left

#include <Servo.h>


Servo myservo;

const int servoPin = 9;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
bool turningRight = false;

int targetAngle = 0;

void setup() {
  pinMode(2, OUTPUT); 
  pinMode(3, INPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, INPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, INPUT); 

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
}
void loop() {
  // Clears the trigPin condition
  myservo.write(90);
  int distanceToLeftOld = -1;
  int distanceToRightOld = -1;
//Look for turn
  bool breakWhile = false;
    int counter = 0;
  distanceToLeftOld = -1;
   distanceToRightOld = -1;
  while(!breakWhile){

  int distanceToLeft = getDistanceLeft();
  int distanceToRight = getDistanceRight();
  Serial.print("LEFT - ");
   Serial.print(distanceToLeft);
   Serial.print(" | ");
   Serial.print(distanceToLeftOld);
    Serial.print("    RIGHT - ");
     Serial.print(distanceToRight);
        Serial.print(" | ");
     Serial.print(distanceToRightOld);
     Serial.println("");
  

  // first corner

  if(distanceToLeftOld == -1 || distanceToRightOld == -1 || distanceToLeftOld == 0 || distanceToRightOld == 0){
    distanceToLeftOld = distanceToLeft;
    distanceToRightOld = distanceToRight;
  }

  if(distanceToLeftOld < (distanceToLeft - 10) && distanceToLeft != 0){
    turningRight = false;
    counter ++;
    
      Serial.println("LEFT Counter");
  }else if(distanceToRightOld < distanceToRight - 10 && distanceToRight != 0){
    turningRight = true;
    Serial.println("RIGHT Counter");
    counter ++;
  }else{
    distanceToLeftOld = distanceToLeft;
    distanceToRightOld = distanceToRight;
    counter = 0;
    Serial.println("RESET Counter");
  }

  if(counter > 3){
    if(turningRight){
      targetAngle += 90;
      Serial.println("Turning RIGHT");
    }else{
      targetAngle += -90;
      Serial.println("Turning LEFT");
    }
    counter = 0;
    breakWhile = true;
    distanceToLeftOld = -1;
  }


}

if(turningRight){
  
myservo.write(120);
}else{
  myservo.write(60);
}

delay(3000);
myservo.write(0);


}

int getDistanceForward(){
    digitalWrite(2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(3, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
 if(distance > 2000){
   return -1;
 }else{
 return distance;
 }
}

int getDistanceRight(){
    digitalWrite(4, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  digitalWrite(4, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(5, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  if(distance > 2000){
   return -1;
 }else{
 return distance;
 }
}

int getDistanceLeft(){
    digitalWrite(6, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(7, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

 if(distance > 2000){
   return -1;
 }else{
 return distance;
 }

}

