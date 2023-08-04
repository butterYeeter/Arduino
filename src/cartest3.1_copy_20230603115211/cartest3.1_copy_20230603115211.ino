

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

int ultrasonicWait = 20;

void setup() {
  pinMode(2, OUTPUT); //trig
  pinMode(3, INPUT);  //echo
  pinMode(4, OUTPUT); //trig
  pinMode(5, INPUT);  //echo
  pinMode(6, OUTPUT); //trig
  pinMode(7, INPUT);  //echo
   pinMode(10, OUTPUT); //trig
  pinMode(11, INPUT);  //echo

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  delay(500);
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(98);
}
void loop() {
  // First turn, does not know what direction
 
 bool turningRight =  firstTurn();

  turn(turningRight);

  measure()


  

}








}

void turn(turningRight){
  if(turningRight){
  
myservo.write(128);
}else{
  myservo.write(68);
}

delay(2800);
myservo.write(98);

}

void measure(){

 myservo.write(98);
  int distanceToLeftOld = -1;
  int distanceToRightOld = -1;
//Look for turn
  bool breakWhile = false;
    int counter = 0;
  distanceToLeftOld = -1;
   distanceToRightOld = -1;
  while(!breakWhile){

  int distanceToLeft = getDistanceLeft();
  delay(ultrasonicWait);
  int distanceToRight = getDistanceRight();
   delay(ultrasonicWait);
  int distanceBackRight = getDistanceBackRight();
   delay(ultrasonicWait);
  int estAngle = getAngle(distanceToRight, distanceBackRight);

  Serial.print("LEFT - ");
   Serial.print(distanceToLeft);
   Serial.print(" | ");
   Serial.print(distanceToLeftOld);


   
    Serial.print("    RIGHT - ");
     Serial.print(distanceToRight);
        Serial.print(" | ");
     Serial.print(distanceToRightOld);
    
  
         Serial.print("    RIGHT Back - ");
   Serial.print(distanceBackRight);


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

  if(counter > 1){
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

bool firstTurn(){
    myservo.write(98);
  int distanceToLeftOld = -1;
  int distanceToRightOld = -1;
//Look for turn
  bool breakWhile = false;
    int counter = 0;
  distanceToLeftOld = -1;
   distanceToRightOld = -1;
  while(!breakWhile){

  int distanceToLeft = getDistanceLeft();
   delay(ultrasonicWait);
  int distanceToRight = getDistanceRight();
    delay(ultrasonicWait);
  int distanceBackRight = getDistanceBackRight();
   delay(ultrasonicWait);
  int estAngle = getAngle(distanceToRight, distanceBackRight);

  Serial.print("LEFT - ");
   Serial.print(distanceToLeft);
   Serial.print(" | ");
   Serial.print(distanceToLeftOld);


   
    Serial.print("    RIGHT - ");
     Serial.print(distanceToRight);
        Serial.print(" | ");
     Serial.print(distanceToRightOld);
    
  
         Serial.print("    RIGHT Back - ");
   Serial.print(distanceBackRight);


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

  if(counter > 1){
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
return turningRight;

}




int getAngle(int front, int back){

if(back == front){
  myservo.write(98);

}
else if(back-1 > front){
   myservo.write(68);

} else if (back < front-1){
  myservo.write(128);
}
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
   return 200;
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
   return 200;
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
   return 200;
 }else{
 return distance;
 }

}

int getDistanceBackRight(){
    digitalWrite(10, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(10);
  digitalWrite(10, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(11, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

 if(distance > 2000){
   return 200;
 }else{
 return distance;
 }

}

