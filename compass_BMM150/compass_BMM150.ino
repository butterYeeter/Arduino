/**
    This example
*/

#include <Arduino.h>
#include <Wire.h>
// libraries
#include "bmm150.h"
#include "bmm150_defs.h"

BMM150 bmm = BMM150();

float headingOfset, xyOfset, zxOfset;


void setup() {
    Serial.begin(9600);

    if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
        Serial.println("Chip ID can not read!");
        while (1);
    } else {
        Serial.println("Initialize done!");
    }


    delay(1000);
    getCompassOfset();

}

void loop() {
 getCompass();
 delay(100);
}


void getCompassOfset(){
getCompass();
delay(500);

bmm150_mag_data value;
    bmm.read_mag_data();

    value.x = bmm.raw_mag_data.raw_datax;
    value.y = bmm.raw_mag_data.raw_datay;
    value.z = bmm.raw_mag_data.raw_dataz;

    float xyHeading = atan2(value.x, value.y);
    float zxHeading = atan2(value.z, value.x);
    float heading = xyHeading;

    if (heading < 0) {
        heading += 2 * PI;
    }
    if (heading > 2 * PI) {
        heading -= 2 * PI;
    }
    float headingDegrees = heading * 180 / M_PI;
    float xyHeadingDegrees = xyHeading * 180 / M_PI;
    float zxHeadingDegrees = zxHeading * 180 / M_PI;

    Serial.print("ZY Heading: ");
    Serial.print(headingDegrees);
    Serial.print("\txy Heading: ");
    Serial.print(xyHeadingDegrees);
    Serial.print("\tzx Heading: ");
    Serial.print(zxHeadingDegrees);


  headingOfset = headingDegrees;
  xyOfset = xyHeadingDegrees;
  zxOfset = zxHeadingDegrees;
    Serial.println();


}

void getCompass(){



     bmm150_mag_data value;
    bmm.read_mag_data();

    value.x = bmm.raw_mag_data.raw_datax;
    value.y = bmm.raw_mag_data.raw_datay;
    value.z = bmm.raw_mag_data.raw_dataz;

    float xyHeading = atan2(value.x, value.y);
    float zxHeading = atan2(value.z, value.x);
    float heading = xyHeading;

    if (heading < 0) {
        heading += 2 * PI;
    }
    if (heading > 2 * PI) {
        heading -= 2 * PI;
    }
    float headingDegrees = (heading * 180 / M_PI) - headingOfset;
    float xyHeadingDegrees = (xyHeading * 180 / M_PI) - xyOfset;
    float zxHeadingDegrees = (zxHeading * 180 / M_PI) - zxOfset;

    Serial.print("ZY Heading: ");
    Serial.print(headingDegrees);
    Serial.print("\txy Heading: ");
    Serial.print(xyHeadingDegrees);
    Serial.print("\tzx Heading: ");
    Serial.print(zxHeadingDegrees);

    Serial.println();
   
}