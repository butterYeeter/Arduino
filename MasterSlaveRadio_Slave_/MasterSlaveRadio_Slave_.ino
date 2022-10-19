#include <RH_ASK.h>   // Include the RH_ASK library
#include <SPI.h>      // Not actually used but needed to compile the RH_ASK library

RH_ASK radio(2000, 11, 12);
 
void setup()
{
    Serial.begin(9600);   // Use this for debugging
 
    // Speed of 2000 bits per second
    // Use pin 11 for reception
    // Use pin 12 for transmission
    
    if (!radio.init())
    {
         Serial.println("Radio module failed to initialize");
    }
}
void loop()
{
  // Create a 32 byte char buffer
  uint8_t receive_buffer[32];
  uint8_t buflen = sizeof(receive_buffer);
 //Serial.println("Message: ");
  // If data is available, print it
  if (radio.recv(receive_buffer, &buflen))
  {
    Serial.print("Message: ");
    Serial.println((char*)receive_buffer);         
  }
}
