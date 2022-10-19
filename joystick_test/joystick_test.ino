#include <Joystick.h>
int X, Y;

Joystick joystick(A0, A1, 13);

void setup() {
  Serial.begin(9600);
}

void loop() {
  joystick.print("X: ", "\tY: ", "\tZ: ", 0, 100);
  X = printX(0, 100);
  Serial.println();
}
