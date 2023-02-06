


#include <SoftwareSerial.h>
#include <Wire.h>

//GPS Libary and initialisation stuff
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>


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

//end of GPS stuff


//Radios

SoftwareSerial HC12(12, 11); //RX then TX



//end of Radios


const int buzzer = 9;


//Libaries for BMP 180 ----


#include <Adafruit_BMP280.h>





Adafruit_BMP280 bmp; // I2C

double baseline; // baseline pressure

double maxAlt = 0;
double alt = 0;

boolean servoDeploy = false;
int deployCounter = 0;
//Variables for accelorometer
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int xaccelfinal, yaccelfinal, zaccelfinal = 0;



int flightState = 0;







void setup() {

  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(13, OUTPUT);

//setup GPS
GPSserial.begin(GPSBaud);

  
  //Setup MPU 6050
  Serial.begin(9600);
 HC12.begin(9600);               // Serial port to HC12


  delay(1000);
 // Serial.println("Initialize MPU6050");
  Serial.println("Initialize MPU6050");
  HC12.write("Initialise GyroScope@ \n");
  Wire.setClock(9600);
  Serial.println("1/7");
  HC12.write("1/7@");
  Wire.begin(1);
  Serial.println("2/7");
   HC12.write("2/7@");
  delay(500);
  Serial.println("3/7");
   HC12.write("3/7@");
  Wire.beginTransmission(MPU_addr);
  Serial.println("4/7");
 HC12.write("4/7@");

  Wire.write(0x6B);  // PWR_MGMT_1 register
  Serial.println("5/7");
   HC12.write("5/7@");
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Serial.println("6/7");
   HC12.write("6/7@");
 Serial.println( Wire.endTransmission(true));
  Serial.println("7/7");
   HC12.write("7/7@");



 // Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).



  //BMP 280 Setup
  Serial.println(F("BMP280 test"));
 HC12.write("Initalise Barometer@");

 if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
                       HC12.write("Unable To intialise Barometer@");
    while (1){
      
      delay(10);
      
      pulseBuzzer() ;
    }
  }

Serial.println("BMP FOUND");
  baseline =  bmp.readPressure();
 HC12.write("Baseline Pressure Read");
  Serial.println("Baseline pressure read@");

   HC12.write("Barometer Initaisation Completed@");
  //END OF BMP 280

  
  startSound();
//delay(5000);

getAccel();
 HC12.write("Accelorometer read@");
Serial.println("Accelorometer read");

alt = getAltitude();
 HC12.write("Altitude Read@");
Serial.println("Altitude read");

for (int i = 0; i<20; i++){
digitalWrite(13, HIGH);
delay(30);
digitalWrite(13,LOW);
delay(30);


}
 HC12.write("@@---------  STARTUP COMPLETE  ---------@@");
}

void loop() {

 boolean awaitingTakeoff = false;
  while(yaccelfinal <130 and yaccelfinal>50 and flightState == 0){
    if(!awaitingTakeoff){
Serial.println("Waiting for takeoff");
 HC12.write("Awaiting takeoff");
    }
baseline = getPressure();
getAccel();
  }

if(flightState == 0){
   HC12.write("Takeoff Detected");
}
  flightState =1;


if(alt>maxAlt){

  maxAlt = alt;
}

 if(maxAlt > alt+5){
deployCounter++;
  
 }else{
deployCounter= 0;
  
 }

 if(deployCounter > 2){
servoDeploy = true;
  
 }
  getAccel();
alt = getAltitude();
  Serial.println(alt);
  
sendData();


 

//Serial.print("GGA - ");
String GPSGGAString = updateGPS();
//Serial.println(GPSGGAString);

//Serial.println(GetGPSAlt(GPSGGAString));

radio(GPSGGAString);
}

void radio(String GPSPOSSTR){
String radioPacket = "<<";
radioPacket += "ALT=" + String(alt, 2)+",";
radioPacket += "MAT=" + String(maxAlt, 2)+",";
radioPacket += "CHU="+String(servoDeploy)+",";
radioPacket += "XCL="+String(xaccelfinal)+",";
radioPacket += "YCL="+String(yaccelfinal)+",";
radioPacket += "ZCL="+String(zaccelfinal)+",";
radioPacket += "POS="+GPSPOSSTR+",";


radioPacket += ">>";

  Serial.println(radioPacket);
for (int i = 0; i<radioPacket.length(); i++){
  //Serial.print();
   HC12.write(radioPacket.charAt(i));
}
Serial.println();
HC12.write("@");
}

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

 // Serial.println(GPSRaw.indexOf("2"));

 // Serial.println(GPSRaw);
  
 if(GPSRaw.indexOf("$GNGGA") > -1){
searchPos = GPSRaw.indexOf("$GNGGA");
GGAStart = searchPos;

searchPos = GPSRaw.indexOf("$", searchPos+1);
GGAEnd = searchPos-1;
GGA = GPSRaw.substring(GGAStart, GGAEnd);
Serial.println("GGGGGGAAAAAAAAAAAAAAAAAAAAAAAAAAA");


   Serial.println(GGA);
    return GGA;
 }else{
return "-1";
  //Serial.println("NOT FOUND");
  
 }


 
   
}
void sendData(){

  Serial.println("SENDING PACKETS");

  Wire.beginTransmission(4);
  sendInt(alt);
  
  sendInt(xaccelfinal);
  sendInt(yaccelfinal);
  sendInt(zaccelfinal);



  Wire.write(servoDeploy);

 
  Wire.write("#");
 Wire.endTransmission();    // stop transmitting

}
int sendInt(int bigNum){

  byte myArray[2];
  myArray[0] = (bigNum >> 8) & 0xFF;
  myArray[1] = bigNum & 0xFF;

  Wire.write(myArray, 2);

}





double getAltitude()
{
  
  
    
   // tempreture = (int) bmp.readTemperature();
   
  // pressure = (int) bmp.readPressure();
   
    alt = (bmp.readAltitude(baseline));
    Serial.print("                                                                            ");
   Serial.println(alt);
    Serial.println();
return (alt);
  

}

double getPressure(){
double pressure =  bmp.readPressure();
  return(pressure);
}


void getAccel() {


  int16_t xraw, yraw, zraw;
  int16_t xaccelraw, yaccelraw, zaccelraw;
  int divisionValue = 1;
  float xfinal, yfinal, zfinal = 0;

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr, 6); // request a total of 14 registers


  xraw = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yraw = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zraw = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr, 6);
  xaccelraw = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yaccelraw = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zaccelraw = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  divisionValue = 500;
  xfinal += xraw / divisionValue;
  yfinal += yraw / divisionValue;
  zfinal += zraw / divisionValue;
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

  xaccelfinal = (int)(xaccelraw / 150.0);
  yaccelfinal = yaccelraw / -150.0;
  zaccelfinal = zaccelraw / 150.0;
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



void pulseBuzzer() {

  tone(buzzer, 329);
  delay(250);
  noTone(buzzer);
  delay(250);


}

void startSound() {

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
void startSound2() {

  tone(buzzer, 261.63);
  delay(200);

  tone(buzzer, 349.23);
  delay(500);

  tone(buzzer, 523.25);
  delay(100);

  noTone(buzzer);
  delay(500);


}

void clickBuzzer() {

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

void errorCode() {
  tone(buzzer, 5000);
  delay(500);
  tone(buzzer, 3000);
  delay(200);

  noTone(buzzer);
  delay(1500);
}







int GetGPSAlt(String GGA){
int seaLevelPos = 0;
int searchPos = 0;
int returnAlt = 0;



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
