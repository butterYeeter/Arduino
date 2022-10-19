
/*
 * Interfacing Arduino with BMP280 temperature and pressure sensor.
 * Temperature and pressure values are displayed on 16x2 LCD.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */
 
#include <Wire.h>             // include Wire library, required for I2C devices
#include <Adafruit_Sensor.h>  // include Adafruit sensor library
#include <Adafruit_BMP280.h>  // include adafruit library for BMP280 sensor
 float initialPressure    = 0;
 float temperature =0;
  long int pressure    = 0;
  long int altitude_   = 0;
// define device I2C address: 0x76 or 0x77 (0x77 is library default address)
#define BMP280_I2C_ADDRESS  0x76
 
Adafruit_BMP280 bmp280;
 

 
void setup() {

  Wire.setClock(100000);
  Serial.begin(9600);
 
  // set up the LCD's number of columns and rows

  delay(100);\
  Serial.println("Arduino + BMP280");
  delay(100);\
  Serial.println("Arduino + BMP280");
  delay(100);\
  Serial.println("Arduino + BMP280");
  delay(1000);\
  Serial.println("Arduino + BMP280");
  
  
    delay(100);\
  Serial.println(F("Arduino + BMP280"));
  
  if (!bmp280.begin(BMP280_I2C_ADDRESS))
  {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }else{
    Serial.println("FOund BMP280");
  }
initialPressure    = 1000;
Serial.println(initialPressure);

}
 

 
// main loop
void loop()
{
  // get temperature, pressure and altitude from library
 
 pressure    = bmp280.readPressure();     // get pressure
 altitude_   = bmp280.readAltitude(initialPressure); // get altitude (this should be adjusted to your local forecast)
 temperature = bmp280.readTemperature();  // get temperature
 
 
  // print data on the serial monitor software
  // 1: print temperature
  Serial.print("Temperature = ");
 Serial.print(temperature);
  Serial.print(" °C");
  // 2: print pressure
  Serial.print("   Pressure    = ");
  Serial.print(pressure/162);
  Serial.print(" hPa");
  // 3: print altitude
  Serial.print("   Approx Altitude = ");
  Serial.print(altitude_);

    
  Serial.println();  // start a new line
  delay(100);       // wait 2 seconds
  
}


// end of code.
