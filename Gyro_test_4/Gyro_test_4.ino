#include <SoftwareSerial.h>


#include<Wire.h>

const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t xraw, yraw, zraw;
int16_t xaccelraw, yaccelraw, zaccelraw;
int divisionValue =1;
float xfinal, yfinal, zfinal =0;
float xaccelfinal, yaccelfinal, zaccelfinal =0;
void setup(){
  Serial.begin(9600);
  delay(1000);
  Serial.println("Initialize MPU6050");
  Serial.println("Initialize MPU6050");
  Wire.setClock(9600);
  Serial.println("1/7");
  Wire.begin();
   Serial.println("2/7");
  delay(500);
   Serial.println("3/7");
  Wire.beginTransmission(MPU_addr);
    Serial.println("4/7");
      
  Wire.write(0x6B);  // PWR_MGMT_1 register
   Serial.println("5/7");
Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Serial.println("6/7");
  Wire.endTransmission(true);
   Serial.println("7/7");
    
}
void loop(){
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

  xaccelfinal = xaccelraw/1500.0;
yaccelfinal = yaccelraw/-1500.0;
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
  Serial.println(zaccelfinal);
 
  delay(100);
}
