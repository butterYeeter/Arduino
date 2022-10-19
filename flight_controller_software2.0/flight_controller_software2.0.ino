
#include <Wire.h>
#include <MPU6050.h>
#include <SFE_BMP180.h>
MPU6050 mpu;

SFE_BMP180 pressure;
const int buzzer = 9; //buzzer to arduino pin 9
const int standbyBtn = 2;

float xrot = 0;
float yrot = 0;
float zrot = 0;

float xfor = 0;
float yfor = 0;
float zfor = 0;


int flightState = 0;
int standbyBtnState = 0;

float baseline;
float a, P;
float divisionValue;


void setup() 
{
  
  Serial.begin(9600);
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
delay(2000);
  // Initialize MPU6050
 Serial.println("Initialize MPU6050");
 while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
  //  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // If you want, you can set gyroscope offsets
  // mpu.setGyroOffsetX(155);
  // mpu.setGyroOffsetY(15);
  // mpu.setGyroOffsetZ(15);
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(1);
  
 
//Serial.println("--------------------Gyro initialised--------------------");
pulseBuzzer();
  delay(1000);
  


  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();

Serial.println("--------------------Accelerometer Initialised--------------------");

pulseBuzzer();
delay(1000);
//  Log = SD.open("Flightlog.txt", FILE_WRITE);
 // if (Log) {
Serial.println("File sucsesfully created");
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
  standbyBtnState = digitalRead(standbyBtn);
if(standbyBtnState == HIGH){

flightState = 2;
startSound();
delay(500);
}
}
void writeData(){


  
}

void readAccel()
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

xfor = normAccel.XAxis;
yfor = normAccel.YAxis;
zfor = normAccel.ZAxis;
 
  Serial.print(" Xnorm = ");
  Serial.print(xfor);
  Serial.print(" Ynorm = ");
  Serial.print(yfor);
  Serial.print(" Znorm = ");
  Serial.print(zfor);
  
  delay(10);
}

void readBaro(){
  P = readPressure();
a = pressure.altitude(P, baseline);

Serial.print("relative altitude: ");
if (a >= 0.0) Serial.print(" ");
Serial.print(a, 1);
Serial.print(" meters, ");

}
void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
  Serial.println();
}

void readgyro(){

   Vector normGyro = mpu.readNormalizeGyro();



 
 
divisionValue=14;


xrot += normGyro.XAxis/divisionValue;
yrot += normGyro.YAxis/divisionValue;
zrot += normGyro.ZAxis/divisionValue;
 Serial.print("    X = ");
  Serial.print(xrot);
  Serial.print("    Y = ");
  Serial.print(yrot);
  Serial.print("    Z = ");
  Serial.println(zrot);
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
