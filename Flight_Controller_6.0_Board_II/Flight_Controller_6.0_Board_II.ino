#include <SoftwareSerial.h>

#include <SPI.h>

#include <SPI.h>
#include <SD.h>
#include <Servo.h>

File myFile;

Servo myservo;
const int servoPin = 3;
#include <Wire.h>


int x, y, z;
String sendStr = "";
int baroAlt, pressure, tempreture;

bool servoDeploy = 0;


// CLOCK STuff
#include <virtuabotixRTC.h>
// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(5, 6, 2);

int seconds = 0;
int minutes = 0;



void setup() {
//Clock initialisation
  Serial.begin(9600);           // start serial for output

  Serial.println("INITIALISING CLOCK");
 myRTC.setDS1302Time(0, 0, 0, 7, 14, 9, 2022);
Serial.println("1/1");

Serial.println("INITIALISING WIRE");
  
  // put your setup code here, to run once:
  Wire.begin(4);                // join i2c bus with address #4
Serial.println("1/2");
   Wire.onReceive(receiveEvent); // register event
Serial.println("2/2");

Serial.println("INITIALISING SD CARD");

  if (!SD.begin(4)) {
    Serial.println(" SD initialization failed!");
    while (1);
  }
  Serial.println("1/4");
  pinMode(8, INPUT);



  myFile = SD.open("FLIGHT.txt", FILE_WRITE);
Serial.println("2/4");
 

  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("FLIGHTLOG");
  } else {

    Serial.println("The file did not open");
    while (1);
  }
  Serial.println("3/4");
  myFile.close();
  Serial.println("4/4");
  myservo.attach(servoPin);
  myservo.write(180);

delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

//updateTime();

  if (servoDeploy == true) {

    myservo.write(30);

    delay(1000);
     myservo.write(180);
    Serial.println("HHHHHHHHHHHEEEEEEEEEERRRRRRRRRRRRRRREEEEEEEEEEEEEEEEE");
  } else {

    myservo.write(180);

  }

  

}


void updateTime(){

   myRTC.updateTime();
  // Start printing elements as individuals
 /* Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);*/
  // Delay so the program doesn't print non-stop
seconds = myRTC.seconds;
minutes = myRTC.minutes;

//Serial.print(minutes);
//.print(":");
//Serial.println(seconds);
  
}

void receiveEvent(int howMany)
{
  updateTime();
  digitalWrite(13,HIGH);
  sendStr = "";
  baroAlt = unpackWire();
 // Serial.print(baroAlt);
  //Serial.print(" X=");
  x = unpackWire();
//  Serial.print(x);
//  Serial.print("  Y=");
  y =  unpackWire();
//  Serial.print(y);
 // Serial.print("  Z=");
  z =  unpackWire();
 // Serial.print(z);

 

  

  servoDeploy = Wire.read();

 // Serial.print("  Servo = ");
 // Serial.print(servoDeploy);
 // Serial.println("              ");

  Wire.read();
  while (0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character

    sendStr += c;
    Serial.print(c);         // print the character
  }

myFile =  SD.open("FLIGHT.txt", FILE_WRITE);
myFile.print("Mission Time [");
myFile.print(minutes);
myFile.print(":");
myFile.print(seconds);
myFile.print("] ");
myFile.print("Barometric Altiude: ");
myFile.print(baroAlt);
myFile.print(", Accel X: ");
myFile.print(x);
myFile.print(", Accel Y: ");
myFile.print(y);
myFile.print(", Accel z: ");
myFile.print(z);
myFile.print(", SERVO STATE: ");
myFile.println(servoDeploy);
myFile.close();
digitalWrite(13, LOW);

Serial.print("Mission Time [");
Serial.print(minutes);
Serial.print(":");
Serial.print(seconds);
Serial.print("] ");
Serial.print("Barometric Altiude: ");
Serial.print(baroAlt);
Serial.print(", Accel X: ");
Serial.print(x);
Serial.print(", Accel Y: ");
Serial.print(y);
Serial.print(", Accel z: ");
Serial.print(z);
Serial.print(", SERVO STATE: ");
Serial.println(servoDeploy);

}

int unpackWire() {

  byte msg1 = Wire.read();
  byte msg2 = Wire.read();

  int returnValue = msg1;
  returnValue = (returnValue << 8) | msg2;

  return returnValue;

}
