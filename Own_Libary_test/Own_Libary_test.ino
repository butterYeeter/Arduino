#include <BMP280GPS.h>

void setup() {
  // put your setup code here, to run once:

}

void loop()
{
  // Write SoftwareSerial data to Serial Monitor

//Serial.println("_______1_________");
String GPSGGAString = updateGPS();

Serial.println(GetGPSAlt(GPSGGAString));

  
}
