# Robot Documentation
<p align=center>
<img title="Meet Chihuahua! Our lovely, crazy robot :P" src="https://github.com/butterYeeter/Arduino/blob/main/v-photos/front.jpg?raw=true" width=75%>
</p>

## Content
- 


## History
Firstly we started this project by splitting our efforts and worked on both an arduino based robot and an ev3 based robot. Due to school restricting the time we had to work on both, more progress was made on the arduino based robot and it was decided to use this for the competition.

## Parts List
The robot is built on a 3D printed chasis designed by a member of the team. All components are fitted to this chasis. The parts list include the following:
2x pi pico, 1x Arduino nao, 1x breadboard, 3x prototyping board, 2x voltmeter, 3x buck convertor, 3x power switch, 1x 6s 1500mah batteries, LEDS, Wrapping Wire, Wheels, Jumpers, 8x TOF sensors, 1X Luna TOF sensor, 1x Ultrasonic sensor, 1x Servo motor, 1x 6v DC motor, 1x gearbox, 1x capacitor (40V 300mF), Barrel conector, BMI 180 Gyro, 2X common anode 7 seg display, Motor Driver and ESP32 CAM

## Board Communication
It is quite a lengthy parts list however we believe all the components are vital. We have 4 microtrollers each serving specific and important functionality. The functions are as follows: 
- Camera(ESP 32) board - handles positioning via video. sends data to the TOF board
<p>
<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.universal-solder.ca%2Fwp-content%2Fuploads%2F2020%2F03%2F2184_5507a683-d21a-4e1b-a165-ac7bec357cb20.jpg&f=1&nofb=1&ipt=e5d1252ea72b2e73f0be1c7b8898891e59f3b16ce268294fbb97dd0f83c573aa&ipo=images" width=20% height=20% title="Picture of ESP32 camera board">
</p>

- Gyro(Pi Pico) board - relative gyro, calculates angle for turning
- TOF(Pi Pico) board - Master I2C board. Does all the distance measuring and logic
<picture>
<img title="A Raspberry Pi Pico is used for both the TOF board and Gyro board" src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn.shopify.com%2Fs%2Ffiles%2F1%2F0174%2F1800%2Fproducts%2FPICOBOARDWHITEANGLE2_1024x1024.jpg%3Fv%3D1616398924&f=1&nofb=1&ipt=053fc17a069d7767fd1dc10b2b5485041eedfcf792e284a995c5a39960d3604d&ipo=images" width=20% height=20%>
</picture>

- Motor Control board - Controls the drive motor via PWM and controls servo for steering
<picture>
<img title="Arduino Nano receives commands for the other boards for steering and driving" src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimgaz.staticbg.com%2Fimages%2Foaupload%2Fbanggood%2Fimages%2FB1%2FF3%2F61701d34-1353-4d42-bc39-ada93e72c7db.JPG&f=1&nofb=1&ipt=1efc27b5edb95d0c9deb1fe0c353feed30bde807e831f4f87d48cdd84f592554&ipo=images" width=20% height=20%>
</picture>

The boards all communicate via the I2C protocol

## Management
 We will now discuss specific management of mobility, power, sensor and obstacle management.

### Mobility
Mobility: Initially a high torgque low RPM motor was used, but the complicated belt system made this impractical. We then switched to a lower torque but much higher speed motor that was compatible with an off the shelf gearbox, this is what we are currently using. Mention the encoded and non-encoded motors. The current motor is also run at a higher voltage than is supposed to and is wired with capacitors to reduce EMF which was interfering with our gyro board causing it to reset.

### Power and sensors
Initialy powered off of a 3s Li-ion battery however the voltage was too high. We then switched to a 2s Li-ion battery however the voltage drop was too great and there was capacity issues. We found it easier to switch to a 6 cell drone battery and use multiple voltage regulators. This is what worked best for us and what is currently in use.

### Obstacle avoidance
Through the series of 8 short range time of flight sensors and one long range one (only one was used to high cost) we created what is essentialy poor man's LIDAR. We then only track the inside walls as we found it the simplest solution for position and owrks best with the short range TOF sensor array. The robot aims to drive between 100 and 300mm away from the inside wall. When the robot no longer detects the inside wall it knows that it should turn. As for the obstacle chanllenge the robot makes use of the camera and TOF array to determine the position of the robot relative to the obstacle as well as the color of the obstacle. It will then hug one of side walls depending on wether is a red or green obstacle.

This documentation provides an in-depth understanding of our robot's design, components, and operational principles. 
