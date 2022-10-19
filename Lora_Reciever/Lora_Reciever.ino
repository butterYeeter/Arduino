#include <SPI.h>
#include <LoRa.h> 
int LED = 3;
String inString = "";    // string to hold input
int val = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  
 // while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }else{

     Serial.println("LoRa initialised");
  }
}
 
void loop() {
  
  // try to parse packet
 int packetSize = LoRa.parsePacket();
  
  if (packetSize) { 
   // Serial.println(packetSize);
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
           
    }
      Serial.println(inString);  
    inString = "";     
    Serial.println(LoRa.packetRssi());    
  }
   

}
