

const int stepperPin = 2;
const int dirPin = 3;

const int ExecuteButtonPin = 6;
const int DirButtonPin = 7;
int DirButtonState;
int ExecuteButtonState;
int movementDist = 1000;
int currentDist = 0;

bool executing = 0;
bool dir = 0;
bool Ydir = 0;


void setup() {
  // put your setup code here, to run once:

pinMode(stepperPin, OUTPUT);
pinMode(dirPin, OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
checkbutton();
  
digitalWrite(dirPin, LOW);
if(executing==1){
for(currentDist = 0; currentDist <= movementDist; currentDist++){

digitalWrite(stepperPin, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPin, LOW);
delayMicroseconds (350);
checkbutton();
}}






}

void checkbutton(){
executing = 1;



}
