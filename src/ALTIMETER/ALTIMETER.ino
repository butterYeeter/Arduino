/*
BMP180 - altimeter
modified on 23 Apr 2019
by Saeed Hosseini @ Electropeak
https://electropeak.com/learn
*/
#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
double baseline;
void setup()
{
Serial.begin(9600);
delay(1000);
Serial.println("REBOOT");
delay(500);
Serial.println("REBOOT");
delay(100);
Serial.println("REBOOT");
delay(100);
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
}
void loop()
{
double a, P;
P = readPressure();
a = pressure.altitude(P, baseline);
Serial.print("relative altitude: ");
if (a >= 0.0) Serial.print(" ");
Serial.print(a, 1);
Serial.println(" meters, ");
delay(1000);
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
   Serial.print(" output ");
  Serial.print(P);
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
