
#include <SoftwareSerial.h>

SoftwareSerial HC12(17, 16); // HC-12 TX Pin, HC-12 RX Pin

int x = 0;

byte incomingByte;
char readBuffer ;


void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
delay(1000);
Serial.println("Radio Initialised");
}

void loop() {
 while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    readBuffer = char(incomingByte);    // Add each byte to ReadBuffer string variable
    x = 1;
  }
  
  if(x == 1){
    if(readBuffer == '@'){
      Serial.println(); 
    }else{
 Serial.print(readBuffer);


    }
    x = 0;
 }}
