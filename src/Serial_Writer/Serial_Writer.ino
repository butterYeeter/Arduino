
#include <SoftwareSerial.h>

SoftwareSerial HC12(12, 11); // HC-12 TX Pin, HC-12 RX Pin

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
  }
  delay(100);
  // ==== Sending data from one HC-12 to another via the Serial Monitor
 HC12.write(x);
 x++;
 Serial.println(x);
 if(x == 200){
  x = 0;

 }
 }
