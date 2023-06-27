#include <BMI160Gen.h>

const int select_pin = 10;
const int i2c_addr = 0x69;

const short int serialAdress = 1;


long int oldTime = 0;
long int gyroValue = 0;
float gyroOfset = -20.79;
void setup() {
  Serial.begin(115200); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device

  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);

checkSerial();
oldTime = millis();
}

void loop() {

int requestCode = checkSerial();

if(requestCode == 0){

Serial.write(gyroValue/130000);

}


integrateZ();

}

int checkSerial(){

 if (Serial.available() > 0) {
   String dataPackets = "";
   while(Serial.available()){
    byte inByte = Serial.read();
   dataPackets += inByte;


     //dataPackets = "<3><120>";
    int address = dataPackets.charAt(1) ;


    if(address == serialAdress){
    int codePos = 4;
    int code = ((dataPackets.charAt(codePos) - 48) *100) +((dataPackets.charAt(codePos+1) - 48) *10) + ((dataPackets.charAt(codePos+2)));
  //Serial.println(address );
 // Serial.println(code);

  return code;

    }
  }
  
 }

return -1;
}

void integrateZ(){


 long int newTime = millis();


  int gx, gy, gz;         // raw gyro values

  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);

  // display tab-separated gyro x/y/z values



  gyroValue += (gz-gyroOfset)*(newTime-oldTime);
  oldTime = newTime;






 
}