
#include <Wire.h>

#include <SFE_BMP180.h>
#include <SPI.h>
#include <SD.h>
File myFile;

SFE_BMP180 pressure;
const int buzzer = PB9; 
const int standbyBtn = PB8;

const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t xraw, yraw, zraw;
int16_t xaccelraw, yaccelraw, zaccelraw;
float xfinal, yfinal, zfinal =0;
float xaccelfinal, yaccelfinal, zaccelfinal =0;

int flightState = 0;
int standbyBtnState = 0;
double totalAlt = 0;

float baseline;
float a, P;
int divisionValue;


void setup() 
{
  delay(1000);
 // Serial.begin(9600);
Serial.println("REBOOT");
if (pressure.begin())
Serial.println("BMP180 init success");
else
{
Serial.println("BMP180 init fail (disconnected?)\n\n");
while (1);
}
baseline = readPressure();
Serial.print("baseline pressure: ");
Serial.print(baseline);
Serial.println(" hpa");
Serial.println("--------------------Altimeter initialised--------------------");
pulseBuzzer();
delay(1000);

  
  Serial.println("Initialize MPU6050");
  Serial.println("Initialize MPU6050");
  Wire.setClock(100000);
  Wire.begin();
  delay(500);
  Wire.beginTransmission(MPU_addr);
   
      
  Wire.write(0x6B);  // PWR_MGMT_1 register
Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
Serial.println("--------------------Accelerometer Initialised--------------------");
pulseBuzzer();
Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");
// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
myFile = SD.open("fli_log", FILE_WRITE);
// if the file opened okay, write to it:
if (myFile) {
Serial.print("Writing to FlightLog.txt...");
myFile.println("Flight Log: ");
myFile.println(" ");



Serial.println("done.");
} else {
// if the file didn't open, print an error:
Serial.println("error opening test.txt");
}


Serial.println("--------------------SDcard Initialised--------------------");
pulseBuzzer();
delay(200);
startSound2();
    flightState = 1;

}




void loop()
{
  
readgyro();
readBaro();
readAccel();
updateState();
writeData();
  


}

void updateState(){

  if(flightState == 1){
  standbyBtnState = digitalRead(standbyBtn);
  
if(standbyBtnState == HIGH){

flightState = 2;
startSound();

myFile.println(" ");
myFile.println(" ");
myFile.println(" ");
myFile.println("Standby for launch: ");
delay(500);
}}else if(flightState ==2)[

if (zaccelfinal>13){
myFile.println(" ");
myFile.println(" ");
myFile.println(" ");
myFile.println("Launch detected - Powered flight");
flightState = 3;

}

}


}
void writeData(){

  //write Gyro data
myFile.print("Gyro reletive position: ");
myFile.print("X = ");
myFile.print(xfinal);
myFile.print("Y = ");
myFile.print(yfinal);
myFile.print("Z = ");
myFile.println(zfinal);

//write accelorometer Data
myFile.print(" Accelorometer readings:  ");
myFile.print("X = ");
myFile.print(xaccelfinal);
myFile.print("Y = ");
myFile.print(yaccelfinal);
myFile.print("Z = ");
myFile.println(zaccelfinal);
  
}

void readAccel()
{
Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr,6);
  xaccelraw=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yaccelraw=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zaccelraw=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
 xaccelfinal = xaccelraw/1500.0;
yaccelfinal = yaccelraw/1500.0;
zaccelfinal = zaccelraw/1500.0;
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
  Serial.print(zaccelfinal);
}

void readBaro(){
  P = readPressure();
a = pressure.altitude(P, baseline);

Serial.print("relative altitude: ");
if (a >= 0.0) Serial.print(" ");
Serial.print(a, 1);
Serial.print(" meters, ");
totalAlt += a;
Serial.print("total altitude: ");
Serial.print(a);

}


void readgyro(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission();
  Wire.requestFrom(MPU_addr,6);  // request a total of 14 registers

 
 xraw=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  yraw=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  zraw=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

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
  Serial.println(zfinal);
  
}
double readPressure()
{
char status;
double T, P, p0, a;
status = pressure.startTemperature();
if (status != 0)
{
delay(status);
status = pressure.getTemperature(T);
if (status != 0)
{
status = pressure.startPressure(3);
if (status != 0)
{
delay(status);
status = pressure.getPressure(P, T);
if (status != 0)
{

  
return (P);


}
else Serial.println("error retrieving pressure measurement\n");
}
else Serial.println("error starting pressure measurement\n");
}
else Serial.println("error retrieving temperature measurement\n");
}
else Serial.println("error starting temperature measurement\n");


} 
void pulseBuzzer(){

tone(buzzer, 329); 
 delay(250);      
noTone(buzzer);
delay(250); 


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
