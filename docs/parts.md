# Parts Documentation

The robot is built on a 3D printed chasis designed by a member of the team. All components are fitted to this chasis. The parts list include the following:
- 2x [Raspberry Pi Pico](#pi-pico)
- 1x [Arduino nano](#arduino-nano)
- 1x Breadboard
- 3x Prototyping board
- 2x Voltmeter
- 3x Buck convertor
- 3x Switches
- 1x 6s 1500mah batteries
- 8x [TOF sensors](#time-of-flight-sensors)
- 1X [Luna TOF sensor](#time-of-flight-sensors)
- 1x Ultrasonic sensor
- 1x Servo motor
- 1x 6v DC motor
- 1x Gearbox
- 1x Capacitor (40V 300mF)
- 1x Barrel conector
- 1x [BMP 180 Gyro](#bmp-180)
- 2X Common anode 7 segment display
- 1x Motor Driver
- 1x [ESP32 Cam](#esp-32-cam)
- LEDS
- Wrapping Wire
- Wheels
- Jumpers

## Pi Pico
The Raspberry Pi Pico is a powerful dual core micro controller that runs at 160 MHz. We chose this board due to its cheap price and processing power which is able to keep up with our requirements. Docs [here](/docs/pico.pdf) (See page 17 and 24 for brief usage info)

## Arduino Nano
The Nano is a cheap small sbc that runs at 16 MHz. Initially our robot Chihuahua used 3 of these for sensor, motor and gyro management, however it lacked the processing power for the latter 2 functions. The motor control board is still a nano to this day as it is a basic task. Docs [here](/docs/nano.pdf) (See page 8)

## Time Of Flight Sensors
Time of flight sensors work by sending out a laser signal and measuring the time it takes to come back. We use an array of these for our positioning system. However due to the high costs of long range sensors we mainly use short range ones which are adequate. Data sheet [here](/docs/tof.pdf) (See page 16 for Control Interface info)

## BMP 180
Our dear gyro who we have to thank for steering. It works in combination with the TOF sensors to maintain the robots position and also is required for accurate turning. Data sheet [here](/docs/bmp180.pdf)


## Esp 32 cam
This board helps us to figure out the positions of obstacles. The obstacle avoidance is still in progress. The camera runs at a fairly low resolution as the Esp32 has trouble processing high resolution(Quite shocking just how demanding video is.) Which allows it to run at a decent fps. Due to issues the obstacle challenge isn't our main focus. More info on the board [here](/docs/esp32cam.pdf) These docs aren't for our board but Esp32 camera boards are quite generic so this doc is fine.
