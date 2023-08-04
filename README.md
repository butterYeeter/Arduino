# Robot Documentation

Firstly we started this project by splitting our efforts and worked on both an arduino based robot and an ev3 based robot. Due to school restricting the time we had to work on both, more progress was made on the arduino based robot and it was decided to use this for the competition.

The robot is built on a 3D printed chasis designed by a member of the team. All components are fitted to this chasis. The parts list include the following:
2x pi pico, 1x Arduino nao, 1x breadboard, 3x prototyping board, 2x voltmeter, 3x buck convertor, 3x power switch, 1x 6s 1500mah batteries, LEDS, Wrapping Wire, Wheels, Jumpers, 8x TOF sensors, 1X Luna TOF sensor, 1x Ultrasonic sensor, 1x Servo motor, 1x 6v DC motor, 1x gearbox, 1x capacitor (40V 300mF), Barrel conector, BMI 180 Gyro, 2X common anode 7 seg display, Motor Driver and ESP32 CAM

It is quite a lengthy parts list however we believe all the components are vital. We have 4 microtrollers each serving specific and important functionality. The functions are as follows: 
Camera(ESP 32) board - handles positioning via video. sends data to the TOF board
Gyro board - relative gyro, calculates angle for turning
Motor Control board - controls the motor via PWM
TOF board - Master I2C board. Does all the distance measuring and logic

# Management
-All boards communicate via I2C. We will now discuss specifi management of mobility, power, sensor and obstacle management.
