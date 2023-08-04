
#include <SoftwareSerial.h>

SoftwareSerial HC12(9, 10); // HC-12 TX Pin, HC-12 RX Pin

int x = 0;

byte incomingByte;
String readBuffer = "";


void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12

}

void loop() {
 while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
    x = 1;
  }
  
  if(x == 1){
 Serial.print(readBuffer);
 readBuffer = "";
 x=0;
 }}
