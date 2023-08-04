#include <SoftwareSerial.h>



const int LEDPin = 2;
int del = 1;
void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(LEDPin, HIGH);
delay(del);
digitalWrite(LEDPin, LOW);
delay(del*10);

Serial.println(del);

}
