# Robot Documentation

> Disclaimer! This repo is a fork of the actual repo used so that we could format it nicely

- [Robot Documentation](#robot-documentation)
    - [Mobility Management](#mobility-management)
      - [Robot Version 1](#robot-version-1)
      - [Improvements](#improvements)
    - [Power and Sense Management](#power-and-sense-management)
      - [Robot Version 1](#robot-version-1-1)


### Mobility Management
#### Robot Version 1
In the first version of the **'robot'**, the **motors were managed by an [Arduino Nano](/docs/nano.pdf)**. We **communicated with board via [I2C](https://en.wikipedia.org/wiki/I%C2%B2C)**. The main board(a [Pi Pico](/docs/pico.pdf)) sent what speed the motors should be run. The **motor speed was controlled via [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation)**. High torque low rpm motors were used in the beginning however we ran into issues with the complicated belt system used to drive the wheels. 
 
We then **switched to a lower torque but high rpm brushed dc motor** which was **compatible with an 'off the shelf' gear box**. The motor was also run at a higher than recomended voltage and was **wired with capicitors to reduce EMF**(Which was causing our gyro control board to reset). Steering was handled using another **pi pico with a gyro sensor attached**. This board **controlled a servo using PWM** which controlled the steering rack. The main board communicated(via I2C) the target angle the gyro board should maintain using the steering rack.

The **old chasis** was a combination of 3D printing([Model available here](/models/body_v2.stl)) and hand cut MDF board. The model was a modification(done in Fusion 360) of a base design provided to us by our club. All the control boards as well as the the motor, gear box, servo, gyro, battery and boost converters were **mounted to this chasis**. The TOF sensors used for naviation were mounted to an **mdf frame**(which was connected to the chasis).

<p>
    <img style="height:200px" title="The drive motor" src="https://epro.pk/wp-content/uploads/2017/11/dc-motor-6V.jpg">
    <img title="Meet Chihuahua! Our lovely, crazy robot :P" src="https://github.com/butterYeeter/Arduino/blob/main/v-photos/front.jpg?raw=true" style="height:200px">
</p>

#### Improvements
After the provintial round of the competition, a major <span style="color:lightgreen; background-color:beige    ">decision was made to completely redesign the robot</span>. A new chasis was designed(available ```[here](/models/body_v2.stl)```) and is **completely 3D printed**. This helped improve on the flimsy nature of the old MDF frame. **Components** of the old design was **reused** such as the servo for steering as well as the gearbox. The chasis consists of an **interior chasis for mounting components**, steering rack and motors and an **exterior chasis that acts as a bumper**. 

A choice was made to use **2 drive motors**(connected to the same axle) for **increased torque**(initially a decision was made to ram into the walls according to which traffic sign is seen by the camera). Previously **8 [Time of Flight](/docs/tof.pdf) sensors was used** however we then **switched to one fancy 360 degrees scanning lidar**. This is mounted in the center of the chasis and **no other components sit above it to prevent inteference with the measurements**. On top of the lidar, a **```pixy cam``` is mounted on a servo to scan for traffic signs**.


### Power and Sense Management
#### Robot Version 1
The first version of the robot was powered using a 3 cell Li-PO battery however we ran into issues. We then tested using a 2 cell Li-PO however the voltage drop was too great and their were capacity issues.  We ulitmately switched to a 6 cell battery in combination with voltage regulators. 

A variety of sensors were used in this first robot for 

