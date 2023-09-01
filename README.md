# Robot Documentation
<p align=center>
<img title="Meet Chihuahua! Our lovely, crazy robot :P" src="https://github.com/butterYeeter/Arduino/blob/main/v-photos/front.jpg?raw=true" width=75%>
</p>

## <u>**Table of Contents**</u>
- [History](#history)
- [Parts](#parts)
- [Board-Details](#board-communication)
- [Parts Design](#parts-design)
- [Management](#management)
  - [Mobility](#mobility)
  - [Power-and-Sensors](#power-and-sensors)
  - [Obstacle-Avoidance](#obstacle-avoidance)
- [Software Implementation](#software-implementation)
  - [Global Variables](#global-variables)
  - [Macro Definitions](#macro-definitions)
  - [Modules](#modules)

## [**History**](/docs/history.md#history)
Firstly we started this project by splitting our efforts and worked on both an arduino based robot and an ev3 based robot. Due to school restricting the time we had to work on both, more progress was made on the arduino based robot and it was decided to use this for the competition.
More info [here](/docs/history.md)

## [**Parts**](/docs/parts.md)

<details open>

<summary>List of all the parts</summary>

 - 2x Raspberry Pi Pico
 - 1x Arduino nano
 - 1x Breadboard
 - 3x Prototyping board
 - 2x Voltmeter
 - 3x Buck convertor
 - 3x Switches
 - 1x 6s 1500mah batteries
 - 8x TOF sensors
 - 1X Luna TOF sensor
 - 1x Ultrasonic sensor
 - 1x Servo motor
 - 1x 6v DC motor
 - 1x Gearbox
 - 1x Capacitor (40V 300mF)
 - 1x Barrel conector
 - 1x BMI 180 Gyro
 - 2X Common anode 7 segment display
 - 1x Motor Driver
 - 1x ESP32 Cam
 - LEDS
 - Wrapping Wire
 - Wheels
 - Jumpers

</details>

 More info can be found [here](/docs/parts.md)

## **Board Communication**

It is quite a lengthy parts list however we believe all the components are vital. We have 4 microtrollers each serving specific and important functionality. The functions are as follows: 
- Camera(ESP 32) board - handles positioning via video. sends data to the TOF board
<p align=left>
<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.universal-solder.ca%2Fwp-content%2Fuploads%2F2020%2F03%2F2184_5507a683-d21a-4e1b-a165-ac7bec357cb20.jpg&f=1&nofb=1&ipt=e5d1252ea72b2e73f0be1c7b8898891e59f3b16ce268294fbb97dd0f83c573aa&ipo=images" width=20% height=20% title="Picture of ESP32 camera board">
</p>

- Gyro(Pi Pico) board - relative gyro, calculates angle for turning
- TOF(Pi Pico) board - Master I2C board. Does all the distance measuring and logic
<p align=left>
<img title="A Raspberry Pi Pico is used for both the TOF board and Gyro board" src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn.shopify.com%2Fs%2Ffiles%2F1%2F0174%2F1800%2Fproducts%2FPICOBOARDWHITEANGLE2_1024x1024.jpg%3Fv%3D1616398924&f=1&nofb=1&ipt=053fc17a069d7767fd1dc10b2b5485041eedfcf792e284a995c5a39960d3604d&ipo=images" width=20% height=20%>
</p>

- Motor Control board - Controls the drive motor via PWM and controls servo for steering

<p>
<img title="Arduino Nano receives commands for the other boards for steering and driving" src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimgaz.staticbg.com%2Fimages%2Foaupload%2Fbanggood%2Fimages%2FB1%2FF3%2F61701d34-1353-4d42-bc39-ada93e72c7db.JPG&f=1&nofb=1&ipt=1efc27b5edb95d0c9deb1fe0c353feed30bde807e831f4f87d48cdd84f592554&ipo=images" width=20% height=20%>
</p>

The boards all communicate via the I2C protocol.

## **Parts Design**
This section is to document the design on the mdf board parts and 3D printed chasis. The mdf board parts were designed and cut by hand. The 3D printed chasis and steering components were designed int Fusion 360 and made on Michael's printer. There are some bolts to hold the steering rack together and hot glue to hold the various electronics to the chasis. 3D model of chasis [here](/models/body_v2.stl)

<p>
<img style="width: 400px; height: 400px; object-fit: cover; object-positon: 50% 100%" title="Hot glue mess" src="./v-photos/back.jpg">
</p>


## **Management**
 We will now discuss specific management of mobility, power, sensor and obstacle management.

### *Mobility*
Mobility: Initially a high torque low RPM motor was used, but the complicated belt system made this impractical. We then switched to a lower torque but much higher speed motor that was compatible with an off the shelf gearbox, this is what we are currently using. ```Mention the encoded and non-encoded motors.``` The current motor is also run at a higher voltage than is supposed to and is wired with capacitors to reduce EMF which was interfering with our gyro board causing it to reset.

### *Power and sensors*
Initialy powered off of a 3s Li-ion battery however the voltage was too high. We then switched to a 2s Li-ion battery however the voltage drop was too great and there was capacity issues. We found it easier to switch to a 6 cell drone battery and use multiple voltage regulators. This is what worked best for us and what is currently in use.

### *Obstacle avoidance*
Through the series of 8 short range time of flight sensors and one long range one (only one was used to high cost) we created what is essentialy poor man's LIDAR. We then only track the inside walls as we found it the simplest solution for position and owrks best with the short range TOF sensor array. The robot aims to drive between 100 and 300mm away from the inside wall. When the robot no longer detects the inside wall it knows that it should turn. As for the obstacle chanllenge the robot makes use of the camera and TOF array to determine the position of the robot relative to the obstacle as well as the color of the obstacle. It will then hug one of side walls depending on wether is a red or green obstacle.

This documentation provides an in-depth understanding of our robot's design, components, and operational principles. We have had fun working on these robots and hope to pass through to nationals. I actually had a lot of fun write the Markdown for this doc lol.


## **Software Implementation**
### *Global Variables*
```C
TFLI2C tflI2C;

int16_t tfAddr = TFL_DEF_ADR;    // default I2C address
uint16_t tfFrame = TFL_DEF_FPS;  // default frame rate

int16_t tfDist = 0;  // distance in centimeters
int16_t tfFlux = 0;  // signal quality
int16_t tfTemp = 0;  // temperature in 0.01 degree Celsius

// other device variables
uint16_t tfTime = 0;  // devie clock in milliseconds
uint8_t tfVer[3];     // device version number
uint8_t tfCode[14];   // device serial number

const short int serialAdress = 3;

//ControlPins
const int frontPin = 15;
const int Right45Pin = 12;
const int frontRightPin = 11;
const int Left45Pin = 14;
const int frontLeftPin = 13;
const int backRightPin = 10;
const int backLeftPin = 9;
const int backPin = 16;

//Create the sensor objects
Adafruit_VL53L0X front = Adafruit_VL53L0X();
Adafruit_VL53L0X right45 = Adafruit_VL53L0X();
Adafruit_VL53L0X frontRight = Adafruit_VL53L0X();
Adafruit_VL53L0X left45 = Adafruit_VL53L0X();
Adafruit_VL53L0X frontLeft = Adafruit_VL53L0X();
Adafruit_VL53L0X backRight = Adafruit_VL53L0X();
Adafruit_VL53L0X backLeft = Adafruit_VL53L0X();
Adafruit_VL53L0X back = Adafruit_VL53L0X();



//Create the RanginemeasurementData object to hold the measurement data
VL53L0X_RangingMeasurementData_t frontMeas;
VL53L0X_RangingMeasurementData_t right45Meas;
VL53L0X_RangingMeasurementData_t frontRightMeas;
VL53L0X_RangingMeasurementData_t left45Meas;
VL53L0X_RangingMeasurementData_t frontLeftMeas;
VL53L0X_RangingMeasurementData_t backRightMeas;
VL53L0X_RangingMeasurementData_t backLeftMeas;
VL53L0X_RangingMeasurementData_t backMeas;


//IndicatorLED constants
const int redLED = 6;
const int greenLED = 7;
const int blueLED = 8;

// Global variables for keeping all the distance values from the 8 short range TOF sensors
int frontVal;
int right45Val;
int frontRightVal;
int left45Val;
int frontLeftVal;
int backRightVal;
int backLeftVal;
int backVal;

const int echoPin = 27;
const int trigPin = 26;

const float pi = 3.14159265358979; // Constant float for PI

bool turningRight; // Is the robot turning right

int8_t motorState = 0;
int targetAngle = 0;    // Angle that the robot should currently be parallel with.

int wallNum = 1;    // To keep track of number of times the robot has gone around the track

// Series of variables for help in positioning
int firstWallDist = -1; 
int secondWallDist = -1;
int thirdWallDist = -1;
int fourthWallDist = -1;

int deg90 = 90;
int turnOffset = 5;
```

### *Macro Definitions*
```C
// I2C addresses of the TOF sensors
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34
#define LOX6_ADDRESS 0x35
#define LOX7_ADDRESS 0x36
#define LOX8_ADDRESS 0x37
```

### *Modules*
```C
void lookAtSide();

// Function which makes the robot follow along the inner wall
void alongWall();

// void *movement() functions records important data in the first lap for later use.
void firstmovement();
void secondMovement();
void thirdMovement();
void firstmovement();

// void readAll() receives distance data from all the TOF sensors
void readAll();

// setMotor(int8_t  motorNum) sets the speed of the drive motor
void setMotor(int8_t motorNum);

//  read angle returns the current angle of the robot as an int
int readAngle();
// Sets the current target angle to folow
void setAngle(int targetAngle);

// Reads gyro data of I2C and receives the rate of rotation
int checkGyro();

// This function checks the serial bus for any important data
int checkSerial();

// send*(int sendInt) functions split the 16 bit integer into 2 bytes and send them over serial and I2C protocols respectively
void sendInt(int sendInt);
void sendWireInt(int sendInt);
// Inverse of the send*() functions. Just receive a 16 bit int over serial and I2C respectively
int recieveInt();
int recieveWireInt();

// Halts execution until a target turn is complete
void waitForTurn();

// int read*() functions just read distance data from a specified TOF sensor using the appropriate postfix after read. Data returned as an int. These functions exist because reading data from all the TOF sensors at once is too slow
int readFront();
int readRight45();
int readFrontRight();
int readLeft45();
int readLeft45();
int readBackLeft();
int readBackRight();
int readBack();

// This funciton just setups all the TOF sensors and specifies their individual I2C addresses
void setUpSensors();

// This utility function displays custom error codes through the indicator LED's that are part of the robot. Extremely useful for debugging and better than Serial monitor because Serial.println is really slow
void setUpFailedError(int code);

// This boots up the fancy Luna TOF and does a self check.
void bootTFLuna(uint8_t adr);

// This reads data from the fancy TOF and returns it as an int.
int getLIDAR();

// Displays all the distance data from the 8 short range TOF sensors in the Serial Monitor.
void displayAllDistances();
```

