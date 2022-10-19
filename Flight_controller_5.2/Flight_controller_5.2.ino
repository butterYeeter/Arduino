#include <SoftwareSerial.h>

#include <Adafruit_BMP280.h>

#include <Arduino.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>

#include <Wire.h>
#include <SPI.h>

//#include <LoRa.h> 


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
      
      pulseBuzzer() ;
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
  
*/

 Serial.println(F("BMP280 test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */




                  

//Serial.println("Sent Packet");
startSound();

}







    
void loop()
{
  getGPSData();
  for (int i =0; i<7; i++){

  Serial.println("...");


  sendData();

  getAccel();

  getBaro();
  
  }

  GPSRaw = "";
}


void sendData(){

  Serial.println("SENDING PACKETS");

  Wire.beginTransmission(4);
  sendInt(alt);
  
  sendInt(xaccelfinal);
  sendInt(yaccelfinal);
  sendInt(zaccelfinal);


 sendInt(baroAlt);
 sendInt(pressure);
 sendInt(tempreture);

 
  Wire.write("#");
 Wire.endTransmission();    // stop transmitting

}

void getBaro(){
  
    
    tempreture = (int) bmp.readTemperature();
   
   pressure = (int)bmp.readPressure();
   
    baroAlt = (int)(bmp.readAltitude(1013.25)*100);
    Serial.print("BAROMETRIC ALTITUE: ");
   Serial.println(baroAlt);
   Serial.println(pressure);
   Serial.println(tempreture);
    Serial.println();

  
}




int sendInt(int bigNum){

  byte myArray[2];
  myArray[0] = (bigNum >> 8) & 0xFF;
  myArray[1] = bigNum & 0xFF;

  Wire.write(myArray, 2);

}





void getGPSData(){

  pulseBuzzer();
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
  delay(20);
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

 }



void getAccel(){


    Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr,6);  // request a total of 14 registers

 
   xraw=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yraw=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zraw=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr,6);
  xaccelraw=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yaccelraw=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zaccelraw=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  divisionValue=500;
  xfinal += xraw/divisionValue;
  yfinal += yraw/divisionValue;
  zfinal += zraw/divisionValue;
/*
  Serial.print(" X = ");
  Serial.print(xraw);
  Serial.print(" Y = ");
  Serial.print(yraw);
  Serial.print(" Z = ");
  Serial.println(zraw);
*/
   Serial.print(" X = ");
  Serial.print(xfinal);
  Serial.print(" Y = ");
  Serial.print(yfinal);
  Serial.print(" Z = ");
  Serial.print(zfinal);

  xaccelfinal = (int)(xaccelraw/150.0);
  yaccelfinal = yaccelraw/-150.0;
  zaccelfinal = zaccelraw/150.0;
/*
  Serial.print(" X = ");
  Serial.print(xaccelraw);
  Serial.print(" Y = ");
  Serial.print(yaccelraw);
  Serial.print(" Z = ");
  Serial.println(zaccelraw);
*/
   Serial.print(" ACCEL____ X = ");
  Serial.print(xaccelfinal);
  Serial.print(" Y = ");
  Serial.print(yaccelfinal);
  Serial.print(" Z = ");
  Serial.println(zaccelfinal);
 
  delay(100);
}

void pulseBuzzer(){

  tone(buzzer, 329); 
 delay(250);      
  noTone(buzzer);
  delay(250); 


}

void startSound(){

  tone(buzzer, 261.63); 
 delay(100);   
 tone(buzzer, 293.66); 
 delay(100);   
 tone(buzzer, 329.63); 
 delay(100);   
 tone(buzzer, 349.23); 
 delay(100);   
 tone(buzzer, 392); 
 delay(100);   
 tone(buzzer, 440); 
 delay(100);   
 tone(buzzer, 493.88); 
 delay(100);   
 tone(buzzer, 523.25); 
 delay(100);   
    
  noTone(buzzer);
  delay(500); 


}
void startSound2(){

tone(buzzer, 261.63); 
 delay(200);   

 tone(buzzer, 349.23); 
 delay(500);   
 
 tone(buzzer, 523.25); 
 delay(100);   
    
noTone(buzzer);
delay(500); 


}

void clickBuzzer(){

 tone(buzzer, 1000); 
 delay(100);      
 noTone(buzzer);
   tone(buzzer, 2000); 
  delay(300);   
  noTone(buzzer);   
  tone(buzzer, 3000); 
  delay(150);
  noTone(buzzer);   
  tone(buzzer, 5000); 
  delay(350);        
  noTone(buzzer);     
  delay(1500);        
  

  
}
