const int stepperPin = 5;
const int dirPin = 4;
const int enPin = 3;
const int ExecuteButtonPin = 6;
const int DirButtonPin = 7;
int DirButtonState;
int ExecuteButtonState;
int movementDist = 0;
int currentDist = 0;
bool dir = 0;
bool executing = 0;
void setup() {
  // put your setup code here, to run once:

pinMode(stepperPin, OUTPUT);
pinMode(dirPin, OUTPUT);
pinMode(enPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

if (executing==1){
digitalWrite(stepperPin, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPin, LOW);
delayMicroseconds (350);
checkBtn();
}}


  void checkBtn(){
DirButtonState = digitalRead(DirButtonPin);

    if(DirButtonState==HIGH){
if(dir == 0){
  dir = 1;
  digitalWrite(dirPin, HIGH);
  
  
}else{
  digitalWrite(dirPin, LOW);
  dir = 0;
}

  delay(100);

  }
ExecuteButtonState = digitalRead(DirButtonPin);

}
