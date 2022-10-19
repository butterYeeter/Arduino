#include <Adafruit_BMP280.h>

#include <Arduino.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h> 
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <LoRa.h> 


 // Define SoftwareSerial Connection   
#define swsTX 3 // Transmit FROM GPS
#define swsRX 4 // Receive TO GPS

//GPS Baud rate
#define GPSBaud 9600 

//Serial Monitor Baud Rate

TinyGPSPlus gps;
// Include and set up the SoftwareSerial Library

SoftwareSerial GPSserial(swsRX, swsTX);  

Servo myservo; 

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

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


int runs = 0;
bool servoDeploy = 0;

const int buzzer = 8; //buzzer to arduino pin 9


const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t xraw, yraw, zraw;
int16_t xaccelraw, yaccelraw, zaccelraw;
int divisionValue =1;
float xfinal, yfinal, zfinal =0;
int xaccelfinal, yaccelfinal, zaccelfinal =0;

float tempreture;

int pressure;

int baroAlt;

int maxAlt;

int flightState = 0;

void setup()
{

  //Setup MPU 6050
 Serial.begin(9600);
pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
    delay(1000);
  Serial.println("Initialize MPU6050");
  Serial.println("Initialize MPU6050");
  Wire.setClock(9600);
  Wire.begin(1);
  delay(500);
  Wire.beginTransmission(MPU_addr);
   
      
  Wire.write(0x6B);  // PWR_MGMT_1 register
Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);



  //setup serial
 
  Serial.println(F("BMP280 test"));
 

 if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1){
      
      delay(10);
  
    }
  }




   // Start SoftwareSerial  
 GPSserial.begin(GPSBaud);

/*
                   if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 Serial.println("LoRa started");
  


 Serial.println(F("BMP280 test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. 
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating Mode. 
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling 
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling 
                  Adafruit_BMP280::FILTER_X16,      // Filtering. 
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time. 


*/

//Serial.println("Sent Packet");


}



void loop(){


getGPS();
getBaro();
sendData();
  delay(10000);
}







void sendData(){

  Serial.println("SENDING PACKETS");

  Wire.beginTransmission(4);
   Wire.write("@");
  sendInt(alt);
  
 


 sendInt(baroAlt);
 //sendInt(pressure);
    //GPSRaw ="My name is Dr Eggman. It is nice to see you. 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100";
     int loopCounter = 0;
for (int i = 0; i<GPSRaw.length(); i++){
  loopCounter++;
 char sendChar = GPSRaw.charAt(i); 
Wire.write(sendChar);
//Serial.print(".");
Serial.print(sendChar);

if(loopCounter == 15){
  loopCounter = 0;
Wire.endTransmission(); 
 // delay(20);
  Serial.print("...");
    Wire.beginTransmission(4);
}


}
  Wire.write("^");
 Wire.endTransmission();    // stop transmitting

}

void getBaro(){
  
    
    tempreture = (int) bmp.readTemperature();
   
  // pressure = (int) bmp.readPressure();
   
    baroAlt = (int)(bmp.readAltitude(1013.25)*100);
   Serial.println(baroAlt);
    Serial.println();

  
}




int sendInt(int bigNum){

  byte myArray[2];
  myArray[0] = (bigNum >> 8) & 0xFF;
  myArray[1] = bigNum & 0xFF;

  Wire.write(myArray, 2);

}
void getGPS() {
//  if(! GPSserial.begin()){

 GPSserial.begin(GPSBaud);
    
 // }
  // put your main code here, to run repeatedly:
while(!(GPSserial.available() > 0)){
    
    //Serial.println("Waiting for GPS");
    
  }

  for( x = 0; x<=5; x++){
     while (GPSserial.available() > 0){
  // Serial.println(GPSserial.read());
        GPSchar = GPSserial.read();
        GPSRaw.concat(GPSchar);
     //  GPSRaw ="My name is Dr Eggman. It is nice to see you. 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100";
        delay(1);
        x = 0;
     }delay(1);
  
  }
  delay(20);
Serial.println(GPSRaw);
 
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

 // Serial.println(LatLon);

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
  Serial.print("altstring =");
  Serial.println(alt);
    searchPos = GPSRaw.indexOf("$", searchPos+1);
  GGAEnd = searchPos-1;
  GGA = GPSRaw.substring(GGAStart, GGAEnd);
}
