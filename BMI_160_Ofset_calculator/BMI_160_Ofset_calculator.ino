#include <BMI160Gen.h>

const int select_pin = 10;
const int i2c_addr = 0x69;
long int oldTime = 0;
long int gyroValue = 0;
float gyroOfset = 0;
void setup() {
  Serial.begin(115200); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device

  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);

calibrateGyro();

oldTime = millis();
}

void loop() {



}


void calibrateGyro(){


long int totalDrift = 0;

for(int i = 0; i<10000; i++){


int gx, gy, gz;         // raw gyro values

  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);

totalDrift += gz;

}

gyroOfset = totalDrift/10000.0;

Serial.println(gyroOfset);
delay(1000);
}

