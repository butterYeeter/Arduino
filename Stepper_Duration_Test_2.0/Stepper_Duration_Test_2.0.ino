

const int stepperPin = 5;
const int dirPin = 4;
const int enPin = 3;
const int ExecuteButtonPin = 6;
const int DirButtonPin = 7;
int DirButtonState;
int ExecuteButtonState;
int movementDist = 80000;
int currentDist = 0;

bool executing = 0;
bool dir = 0;


void setup() {
  // put your setup code here, to run once:

pinMode(stepperPin, OUTPUT);
pinMode(dirPin, OUTPUT);
pinMode(enPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
checkbutton();
  
movementDist = (int) random(10, 4000);
if(executing==1){

dir = 0;
digitalWrite(stepperPin, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPin, LOW);
delayMicroseconds (350);
checkbutton();

dir =1;
digitalWrite(stepperPin, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPin, LOW);
delayMicroseconds (350);
checkbutton();



}}

void checkbutton(){

ExecuteButtonState = digitalRead(ExecuteButtonPin);

if (ExecuteButtonState == HIGH){
if (executing == 0){
  executing =1;
}else{

  executing =0;
}
delay (500);

}


}
