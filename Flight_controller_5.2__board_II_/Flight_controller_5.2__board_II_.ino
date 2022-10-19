#include <SoftwareSerial.h>

#include <SPI.h>
#include <LoRa.h> 
// Wire Peripheral Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI Peripheral device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>


int GPSAltitiude = 0;

int x, y,z;
String sendStr = "";
 
void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
 Serial.begin(9600);           // start serial for output

  Serial.println("LoRa Sender");
  LoRa.begin(433E6);
 /* if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
*/

  
}

void loop()
{

  LoRa.beginPacket();  
  LoRa.print(GPSAltitiude);
  LoRa.print("#");
   LoRa.print(x);
  LoRa.print("#");
   LoRa.print(y);
  LoRa.print("#");
   LoRa.print(z);
  LoRa.print("#");
  LoRa.print(sendStr);
  LoRa.endPacket();
  delay(50);
// Serial.println("Sent Packet");
 Serial.println("");  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  sendStr = "";
GPSAltitiude = unpackWire();
Serial.print(GPSAltitiude); 
Serial.print("              ");
  x= unpackWire();
 Serial.print(x); 
   Serial.print("              ");
   y =  unpackWire();
 Serial.print(y); 
    Serial.print("              ");
    z =  unpackWire();
    Serial.print(z);
       Serial.print("              ");  
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
