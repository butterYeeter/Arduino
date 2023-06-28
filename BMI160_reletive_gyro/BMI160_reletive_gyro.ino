#include <BMI160Gen.h>
#include <SoftwareSerial.h>
const int select_pin = 10;
const int i2c_addr = 0x69;

const short int serialAdress = 1;

SoftwareSerial comBus(8, 9);  // RX, TX

long int oldTime = 0;
long int gyroValue = 0;
float gyroOfset = -20.79;
void setup() {

  comBus.begin(57600);
  Serial.begin(9600);  // initialize Serial communication
  while (!Serial)
    ;  // wait for the serial port to open

  // initialize device

  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);

  checkSerial();
  oldTime = millis();
}

void loop() {

  int requestCode = checkSerial();


  if (requestCode == 0) {
    comBus.write(2);
    sendInt(gyroValue / 130000);
    Serial.print(gyroValue / 130000);
  }


  integrateZ();
}

int recieveInt() {
  byte b1 = comBus.read();
  byte b2 = comBus.read();

  int returnInt = b1;

  returnInt = returnInt << 8;
  returnInt += b2;

  return returnInt;
}
void sendInt(int sendInt){
  byte b1 = sendInt>>8;
  byte b2 = sendInt;
  comBus.write(b1);
  comBus.write(b2);

}
int checkSerial() {

  if (comBus.available() > 0) {
    String dataPackets = "";

    dataPackets = "";

    //dataPackets = "<3><120>";
    int address = comBus.read();
    Serial.println(address);
    int code = recieveInt();

    if (address == serialAdress) {
      Serial.println(code);
      return code;
    }
  }

  return -1;
}

void integrateZ() {


  long int newTime = millis();


  int gx, gy, gz;  // raw gyro values

  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);

  // display tab-separated gyro x/y/z values



  gyroValue += (gz - gyroOfset) * (newTime - oldTime);
  oldTime = newTime;
}