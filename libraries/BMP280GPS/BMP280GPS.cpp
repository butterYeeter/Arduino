


/*
  SoftwareSerial Echo
  software-serial-echo.ino
  Echos data from SoftwareSerial
  Use to display GPS raw data
  Results on serial monitor

  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

 // Define SoftwareSerial Connection
#define swsTX 3 // Transmit FROM GPS
#define swsRX 4 // Receive TO GPS

//GPS Baud rate
#define GPSBaud 9600

//Serial Monitor Baud Rate
#define Serial_Monitor_Baud 9600
TinyGPSPlus gps;
// Include and set up the SoftwareSerial Library
#include <SoftwareSerial.h>
SoftwareSerial GPSserial(swsRX, swsTX);


int returnAlt;


#include "BMP280GPS.h"

String updateGPS(){
  int searchPos = 0;
  char GPSchar;
 String GGA = "";
String GPSRaw ="";
 int GGAStart = 0;
int GGAEnd = 0;

//Serial.println("_______0_________");
  for(int x = 0; x<=5; x++){
   //   Serial.println("________________");
  while (GPSserial.available() > 0){
 // Serial.write(GPSserial.read());
 GPSchar = GPSserial.read();
GPSRaw.concat(GPSchar);
delay(1);
x = 0;
  }delay(1);}
 if(GPSRaw.indexOf("$GNGGA") > 0){
searchPos = GPSRaw.indexOf("$GNGGA");
GGAStart = searchPos;

searchPos = GPSRaw.indexOf("$", searchPos+1);
GGAEnd = searchPos-1;
GGA = GPSRaw.substring(GGAStart, GGAEnd);

   Serial.println(GGA);
 }

 return GGA;


}




int GetGPSAlt(String GGA){
int seaLevelPos = 0;
int searchPos = 0;




int altPOS;
String altString = "";
//int alt = 0;


 //Serial.println(GPSRaw);


int GGAEnd = 0;


 if(GGA.indexOf(",") > 0){

int endPos = 0;



endPos = GGA.indexOf(",", searchPos + 1);



searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);

searchPos = GGA.indexOf(",", searchPos + 1);
searchPos = GGA.indexOf(",", searchPos + 1);

altPOS = searchPos + 1;
searchPos = GGA.indexOf(",", searchPos + 1);
searchPos = GGA.indexOf(",", searchPos + 1);

seaLevelPos = searchPos+1;

//get Altitude
char chararr[32];
GGAEnd = (GGA.indexOf(",", altPOS));
altString = GGA.substring(altPOS, GGAEnd);
altString.toCharArray(chararr, altString.length() +1);
returnAlt = atof(chararr);

//Get sea level
String seaLevelString;
char chararr2[32];
int seaLevel = 0;
GGAEnd = (GGA.indexOf(",", seaLevelPos));
seaLevelString = GGA.substring(seaLevelPos, GGAEnd);
seaLevelString.toCharArray(chararr2, altString.length() +1);
seaLevel = atof(chararr2);

returnAlt += seaLevel;

delay(100);
return returnAlt;

 }else{

delay(100);
//return(-1);

 }








}
