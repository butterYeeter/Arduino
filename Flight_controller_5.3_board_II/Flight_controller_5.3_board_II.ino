#include <SoftwareSerial.h>

#include <SPI.h>
#include <LoRa.h> 
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
File myFile;

Servo myservo; 



#include <Wire.h>


int GPSAltitiude = 0;

int x, y,z;
String sendStr = "";
 int baroAlt, pressure, tempreture;

 bool servoDeploy = 0;
void setup()
{


  
  Wire.begin(4);                // join i2c bus with address #4

 Serial.begin(9600);           // start serial for output

  Serial.println("LoRa Sender");
  if(!LoRa.begin(433E6)){

Serial.println("Failed to connect to LoRa");

    
  }

  if (!SD.begin(4)) {
Serial.println("initialization failed!");
//while (1);
}
pinMode(8, INPUT);



myFile = SD.open("FLIGHT.txt", FILE_WRITE);

  Wire.onReceive(receiveEvent); // register event

  if(myFile){
Serial.print("Writing to test.txt...");
myFile.println("FLIGHTLOG");

  }else{

    Serial.println("The file did not open");
 //   while(1);
  }

myFile.close();
  myservo.attach(3);
myservo.write(180);
delay(500);





}










void loop()
{

  if(servoDeploy == true){

    myservo.write(0);
    
    delay(1000);
  //  Serial.println("HHHHHHHHHHHEEEEEEEEEERRRRRRRRRRRRRRREEEEEEEEEEEEEEEEE");
  }else{
    myservo.write(180);  
  }


  
 // myFile.open("FLIGHT.txt", FILE_WRITE);

  LoRa.beginPacket();  
  LoRa.print(GPSAltitiude);
  LoRa.print("#  ");
  
  myFile.print(GPSAltitiude);
  myFile.print(",  ");

LoRa.print(baroAlt);
  LoRa.print("#  ");
  
  myFile.print(baroAlt);
  myFile.print(",  ");
  
   LoRa.print(x);
  LoRa.print("#  ");
   myFile.print(x);
  myFile.print(",  ");

  
   LoRa.print(y);
  LoRa.print("#  ");
myFile.print(y);
  myFile.print(",  ");

   
   LoRa.print(z);
  LoRa.print("#  ");
  myFile.print(z);
  myFile.print(",  ");


    LoRa.print(servoDeploy);
  LoRa.print("#  ");
  myFile.print(servoDeploy);
  myFile.print(",  ");
  
  LoRa.print(sendStr);
  LoRa.endPacket();
  delay(50);
// Serial.println("Sent Packet");
 Serial.println("");  
myFile.println(" ");

//myFile.close();


/*
if(digitalRead(8) ==HIGH){

myFile.close();
Serial.println("btn pressed");
  Serial.println("The file is closed");
  Wire.end();
  while(1){
  delay(100);
Serial.println("The file is closed");
  }
*/}



// function that executes whenever data is received from master
// this function is registered as an event, see setup()



void receiveEvent(int howMany)
{
  sendStr = "";
GPSAltitiude = unpackWire();
Serial.print(GPSAltitiude); 
Serial.print(" X=");
  x= unpackWire();
 Serial.print(x); 
   Serial.print("  Y=");
   y =  unpackWire();
 Serial.print(y); 
    Serial.print("  Z=");
    z =  unpackWire();
    Serial.print(z);
       Serial.print("  baroAlt =");  
       baroAlt = unpackWire();
       Serial.print(baroAlt);
       Serial.print("  Temp=");  
      
        tempreture = unpackWire();
       Serial.print(tempreture);
       Serial.print(" ");  

servoDeploy = Wire.read();

       Serial.print("  Servo = ");  
Serial.print(servoDeploy);
       Serial.println("              ");  
       
     Wire.read();  
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
   
    sendStr += c;
    Serial.print(c);         // print the character
  }


  
}

int unpackWire(){

byte msg1 = Wire.read();
byte msg2 = Wire.read();

int returnValue= msg1;
 returnValue = (returnValue<<8)|msg2;

return returnValue;

}
