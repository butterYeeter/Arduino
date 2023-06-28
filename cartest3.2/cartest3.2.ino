#include <SoftwareSerial.h>
#include <PID_v1.h>

//Stuff for PID

double Setpoint, Input, Output;


double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//pins in use by the ultrasonic sensors
// 2 3  Forward
// 4 5  Right
// 6 7  left

#include <Servo.h>
SoftwareSerial comBus(8, 9); // RX, TX

Servo myservo;

const short int serialAdress = 2;

const int servoPin = 9;

// defines variables
long duration;  // variable for the duration of sound wave travel
int distance;   // variable for the distance measurement
bool turningRight = false;

int targetAngle = 0;

int ultrasonicWait = 20;

void setup() {
delay(1000);
  //These are for the ultrasonic sensors
  pinMode(2, OUTPUT);   //trig
  pinMode(3, INPUT);    //echo
  pinMode(4, OUTPUT);   //trig
  pinMode(5, INPUT);    //echo
  pinMode(6, OUTPUT);   //trig
  pinMode(7, INPUT);    //echo
  pinMode(10, OUTPUT);  //trig
  pinMode(11, INPUT);   //echo


  comBus.begin(57600);
  Serial.begin(9600);  // // Serial Communication is starting with 9600 of baudrate speed
  delay(500);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");  // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object
  myservo.write(98);
}


void loop() {
  // First turn, does not know what direction

  //bool turningRight = firstTurn();

  //turn(turningRight);wwwww

  //measure()
  delay(100);
  Serial.println("Checking");
  int angle = checkGyro();

  Serial.println(angle);
}






void sendInt(int sendInt){
  byte b1 = sendInt>>8;
  byte b2 = sendInt;
  comBus.write(b1);
  comBus.write(b2);

}
int recieveInt() {
  byte b1 = comBus.read();
  byte b2 = comBus.read();

  int returnInt = b1;

  returnInt = returnInt << 8;
  returnInt += b2;

  return returnInt;
}

int checkSerial() {

  if (comBus.available() > 0) {
    String dataPackets = "";

    dataPackets = "";

    //dataPackets = "<3><120>";
    int address = comBus.read();
   // Serial.println(address);
    int code = recieveInt();

    if (address == serialAdress) {
      //Serial.println(code);
      return code;
    }
  }

  return -1;
}

int checkGyro(){
digitalWrite(13, HIGH);
  comBus.write(1);  //This must be between 0 and 255

  int checkCode = 0;

  sendInt(checkCode);

  digitalWrite(13,LOW);
  int counter = 0;
  boolean exitLoop = false;
  while(!comBus.available() || exitLoop){
      delay(1);
      counter++;
    if(counter == 300){
      exitLoop = true;
    }


  }
  //Serial.println("Found");
  //digitalWrite(13,HIGH);
  return checkSerial();
  //delay(50);
 // digitalWrite(13, LOW);

}


void turn(bool turningRight) {

  if (turningRight) {

    myservo.write(128);
  } else {
    myservo.write(68);
  }

  delay(2800);
  myservo.write(98);
}

void measure() {

  myservo.write(98);
  int distanceToLeftOld = -1;
  int distanceToRightOld = -1;
  //Look for turn
  bool breakWhile = false;
  int counter = 0;
  distanceToLeftOld = -1;
  distanceToRightOld = -1;
  while (!breakWhile) {

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

    if (distanceToLeftOld == -1 || distanceToRightOld == -1 || distanceToLeftOld == 0 || distanceToRightOld == 0) {
      distanceToLeftOld = distanceToLeft;
      distanceToRightOld = distanceToRight;
    }



    if (distanceToLeftOld < (distanceToLeft - 10) && distanceToLeft != 0) {
      turningRight = false;
      counter++;

      Serial.println("LEFT Counter");
    } else if (distanceToRightOld < distanceToRight - 10 && distanceToRight != 0) {
      turningRight = true;
      Serial.println("RIGHT Counter");
      counter++;
    } else {
      distanceToLeftOld = distanceToLeft;
      distanceToRightOld = distanceToRight;
      counter = 0;
      Serial.println("RESET Counter");
    }

    if (counter > 1) {
      if (turningRight) {
        targetAngle += 90;
        Serial.println("Turning RIGHT");
      } else {
        targetAngle += -90;
        Serial.println("Turning LEFT");
      }
      counter = 0;
      breakWhile = true;
      distanceToLeftOld = -1;
    }
  }
}

bool firstTurn() {
  myservo.write(98);
  int distanceToLeftOld = -1;
  int distanceToRightOld = -1;
  //Look for turn
  bool breakWhile = false;
  int counter = 0;
  distanceToLeftOld = -1;
  distanceToRightOld = -1;
  while (!breakWhile) {

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

    if (distanceToLeftOld == -1 || distanceToRightOld == -1 || distanceToLeftOld == 0 || distanceToRightOld == 0) {
      distanceToLeftOld = distanceToLeft;
      distanceToRightOld = distanceToRight;
    }

    if (distanceToLeftOld < (distanceToLeft - 10) && distanceToLeft != 0) {
      turningRight = false;
      counter++;

      Serial.println("LEFT Counter");
    } else if (distanceToRightOld < distanceToRight - 10 && distanceToRight != 0) {
      turningRight = true;
      Serial.println("RIGHT Counter");
      counter++;
    } else {
      distanceToLeftOld = distanceToLeft;
      distanceToRightOld = distanceToRight;
      counter = 0;
      Serial.println("RESET Counter");
    }

    if (counter > 1) {
      if (turningRight) {
        targetAngle += 90;
        Serial.println("Turning RIGHT");
      } else {
        targetAngle += -90;
        Serial.println("Turning LEFT");
      }
      counter = 0;
      breakWhile = true;
      distanceToLeftOld = -1;
    }
    return turningRight;
  }
}




int getAngle(int front, int back) {

  if (back == front) {
    myservo.write(98);

  } else if (back - 1 > front) {
    myservo.write(68);

  } else if (back < front - 1) {
    myservo.write(128);
  }
}



int getDistanceForward() {
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(3, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
                                    // Displays the distance on the Serial Monitor
  if (distance > 2000) {
    return 200;
  } else {
    return distance;
  }
}

int getDistanceRight() {
  digitalWrite(4, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  digitalWrite(4, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(5, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  if (distance > 2000) {
    return 200;
  } else {
    return distance;
  }
}

int getDistanceLeft() {
  digitalWrite(6, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(7, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
                                    // Displays the distance on the Serial Monitor

  if (distance > 2000) {
    return 200;
  } else {
    return distance;
  }
}

int getDistanceBackRight() {
  digitalWrite(10, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(10);
  digitalWrite(10, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(11, HIGH, 250000);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
                                    // Displays the distance on the Serial Monitor

  if (distance > 2000) {
    return 200;
  } else {
    return distance;
  }
}
