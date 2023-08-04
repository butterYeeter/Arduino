#include <Wire.h>
#include <VL53L0X.h>

VL53L0X leftFrontSensor;
VL53L0X rightFrontSensor;
VL53L0X leftBackSensor;
VL53L0X rightBackSensor;

const int frontLeftSensorPin = 5;
const int frontRightSensorPin = 6;
const int backLeftSensorPin = 7;
const int backRightSensorPin = 8;
int LFD, RFD, LBD, RBD;

void initSensors() {
  pinMode(frontLeftSensorPin, OUTPUT);
  pinMode(frontRightSensorPin, OUTPUT);
  pinMode(backLeftSensorPin, OUTPUT);
  pinMode(backRightSensorPin, OUTPUT);

  digitalWrite(frontLeftSensorPin, LOW);
  digitalWrite(frontRightSensorPin, LOW);
  digitalWrite(backLeftSensorPin, LOW);
  digitalWrite(backRightSensorPin, LOW);

  digitalWrite(frontLeftSensorPin, HIGH);
  delay(150);
  leftFrontSensor.init(true);
  delay(100);
  leftFrontSensor.setAddress((uint8_t)01);

  digitalWrite(frontRightSensorPin, HIGH);
  delay(150);
  rightFrontSensor.init(true);
  delay(100);
  rightFrontSensor.setAddress((uint8_t)02);

  digitalWrite(backLeftSensorPin, HIGH);
  delay(150);
  leftBackSensor.init(true);
  delay(100);
  leftBackSensor.setAddress((uint8_t)01);

  digitalWrite(backRightSensorPin, HIGH);
  delay(150);
  rightBackSensor.init(true);
  delay(100);
  rightBackSensor.setAddress((uint8_t)02);

  leftFrontSensor.startContinuous();
  rightFrontSensor.startContinuous();
  leftBackSensor.startContinuous();
  rightBackSensor.startContinuous();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  initSensors();
}

void loop() {
  LFD = leftFrontSensor.readRangeContinuousMillimeters();
  RFD = rightFrontSensor.readRangeContinuousMillimeters();
  LBD = leftBackSensor.readRangeContinuousMillimeters();
  RBD = rightBackSensor.readRangeContinuousMillimeters();

  Serial.print(F("S1: "));
  Serial.println(LFD);
  Serial.print(F("S2: "));
  Serial.println(RFD);
  Serial.print(F("S3: "));
  Serial.println(LBD);
  Serial.print(F("S4: "));
  Serial.println(RBD);
}
