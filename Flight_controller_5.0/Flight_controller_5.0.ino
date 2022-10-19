#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h> 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LoRa.h> 


 // Define SoftwareSerial Connection   
#define swsTX 3 // Transmit FROM GPS
#define swsRX 4 // Receive TO GPS

//GPS Baud rate
#define GPSBaud 9600 

//Serial Monitor Baud Rate
#define Serial_Monitor_Baud 115200  
TinyGPSPlus gps;
// Include and set up the SoftwareSerial Library

SoftwareSerial GPSserial(swsRX, swsTX);  


//#define BMP_SCK  (13)
//#define BMP_MISO (12)
//#define BMP_MOSI (11)
//#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C


int x = 0;
int searchPos = 0;
int GGAStart = 0;
int GGAEnd = 0;
String GGA = "";
String GPSRaw ="";
String Time = "";
char GPSchar;
int altPOS;
String altString = "";
int alt = 0;
String LatLon = "";
int latlonPos = 0;





void setup()
{
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));
  Wire.begin(1); // join i2c bus (1)


 if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }


   // Start SoftwareSerial  
 GPSserial.begin(GPSBaud);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


                   if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 Serial.println("LoRa started");
  

}
    
void loop()
{



getGPSData();
getBaroData();
sendData();



  GPSRaw = "";
}
void sendData(){

Wire.beginTransmission(2);






 Wire.endTransmission();    // stop transmitting

}


void getBaroData(){

  Serial.print("Approx altitude = ");
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");




  
}
void getGPSData(){


while(!(GPSserial.available() > 0)){
  
   //Serial.println("Waiting for GPS");
  
  }

  for( x = 0; x<=5; x++){
  while (GPSserial.available() > 0){
//  Serial.println(GPSserial.read());
 GPSchar = GPSserial.read();
GPSRaw.concat(GPSchar);
delay(1);
x = 0;
  }delay(1);
  
  }
//Serial.println(GPSRaw);
 
 if(GPSRaw.indexOf("$GNGGA") > 0){
searchPos = GPSRaw.indexOf("$GNGGA");
GGAStart = searchPos;

searchPos = GPSRaw.indexOf("$", searchPos+1);
GGAEnd = searchPos-1;
  GGA = " ";
GGA = GPSRaw.substring(GGAStart, GGAEnd);

  
 }

 Serial.println(GGA);

 //if(GGA.indexOf(",") > 0){
 

  
searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

latlonPos = searchPos;


searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);
LatLon = " ";
LatLon = GGA.substring(latlonPos, searchPos);

Serial.println(LatLon);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);
searchPos = GGA.indexOf(",", searchPos + 1);

altPOS = searchPos + 1;


char chararr[32];
GGAEnd = (GGA.indexOf(",", searchPos + 1));
altString = GGA.substring(altPOS, GGAEnd);
altString.toCharArray(chararr, altString.length() +1);  
alt = atof(chararr);

//alt = toInt();
Serial.println("altstring =");
Serial.println(alt);
searchPos = GPSRaw.indexOf("$", searchPos+1);
GGAEnd = searchPos-1;
GGA = GPSRaw.substring(GGAStart, GGAEnd);

  
// }









}
