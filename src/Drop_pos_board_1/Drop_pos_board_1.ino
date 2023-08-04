//drop pod board 1
#include <Adafruit_BMP280.h>

#include <Arduino.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h> 
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

Adafruit_BMP280 bmp; // I2C
File myFile;

double baroAlt = 0;
double tempreature = 0;
double pressure = 0;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Wire.setClock(9600);
  Wire.begin(1);

 Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  
myFile = SD.open("FLIGHT.txt", FILE_WRITE);

  if(myFile){
Serial.print("Writing to test.txt...");
myFile.println("FLIGHTLOG");

  }else{

    Serial.println("The file did not open");
 //   while(1);
  }
  
myFile.close();
}

void loop() {
  // put your main code here, to run repeatedly:

getBaro();
delay(1000);
writeFile();

delay(1000);
}


void writeFile(){


myFile = SD.open("FLIGHT.txt", FILE_WRITE);
myFile.print("Barometric Altitude: , ");
myFile.print(baroAlt);
myFile.print(",Air Pressure: , ");
myFile.print(pressure);
myFile.print(",Tempreature: , ");
myFile.print(tempreature);

myFile.println();


myFile.close();
  
}
void getBaro(){
  
    
    tempreature = (int) bmp.readTemperature();
   
  pressure = (int) bmp.readPressure();
   
    baroAlt = (int)(bmp.readAltitude(1013.25)*100);
  // Serial.println(baroAlt);
    Serial.println();

  
}
