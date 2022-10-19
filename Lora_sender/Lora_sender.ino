
#include <SPI.h>
#include <LoRa.h> 
int pot = A0;
 int val = 0;
void setup() {
  Serial.begin(9600);
 // pinMode(13,OUTPUT);
  

  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }else{

     Serial.println("LoRa initialised");
  }
}
 
void loop() {
  val ++;
  LoRa.beginPacket();  
  LoRa.print(val);
  //digitalWrite(13, HIGH);
  LoRa.endPacket();
  delay(50);
  //digitalWrite(13, LOW);
 Serial.println("Sent Packet");
 if (val == 100){

val = 0;
 }
 }
