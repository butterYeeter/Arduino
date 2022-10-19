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
char lastChar = '.';
 bool servoDeploy = 0;
void setup()
{


  
  Wire.begin(4);                // join i2c bus with address #4

 Serial.begin(9600);           // start serial for output

  //Serial.println("LoRa Sender");
  if(!LoRa.begin(150E6)){

//Serial.println("Failed to connect to LoRa");

    
  }

  if (!SD.begin(4)) {
//Serial.println("initialization failed!");
//while (1);
}
pinMode(8, INPUT);



myFile = SD.open("FLIGHT.txt", FILE_WRITE);

Wire.onReceive(receiveEvent); // register event

  if(myFile){
//Serial.print("Writing to test.txt...");
myFile.println("FLIGHTLOG");
  }else{

  //  Serial.println("The file did not open");
   // while(1);
  }






}

void loop() {
  // put your main code here, to run repeatedly:
LoRaSend();
delay(100);
 
}

void LoRaSend(){
   if(lastChar == '^'){
 // Serial.println("SENDING DATA");
   LoRa.beginPacket();  
  LoRa.print(GPSAltitiude);
  LoRa.print("#  ");
  
 
LoRa.print(baroAlt);
  LoRa.print("#  ");
 
  
   



  LoRa.print("#  ");
  LoRa.endPacket();
LoRa.endPacket();


LoRa.beginPacket();  

  int sendCounter = 0;
  for (int i = 0; i < sendStr.length(); i++){

  char sendChar = sendStr.charAt(i);
  sendCounter++;
  //  Serial.print(sendChar);
  LoRa.print(sendChar);
delay(2);

if(sendCounter == 200){
 LoRa.endPacket();
delay(100);
LoRa.beginPacket();
  sendCounter = 0;
  delay(100);
 //  Serial.print("....");
}
  }
  
delay(100);
 LoRa.endPacket();
}}


void receiveEvent(int howMany)
{

  char c = Wire.read(); // receive byte as a character
  if(c=='@'){
  sendStr = "Hello ";
GPSAltitiude = unpackWire();
//Serial.print(GPSAltitiude); 


 //      Serial.print("  baroAlt =");  
       baroAlt = unpackWire();

      
//  Serial.print(baroAlt); 

  //     Serial.print(" ");  



    //   Serial.println("              ");  
  }
  if(c!='@'){
     sendStr += c;
   // Serial.print(c);         // print the character
 lastChar = c;
  }
  while(0 < Wire.available()) 
  {
    
    c = Wire.read(); // receive byte as a character
    sendStr += c;
    lastChar = c;
   // Serial.print(c);         // print the character
  
 
  }
  //Serial.println("Msg not over ");  
  delay(1);
//  Serial.println(lastChar);
 if(lastChar == '^'){
//Serial.println(sendStr);
 }

 
}

int unpackWire(){

byte msg1 = Wire.read();
byte msg2 = Wire.read();

int returnValue= msg1;
 returnValue = (returnValue<<8)|msg2;

return returnValue;

}
