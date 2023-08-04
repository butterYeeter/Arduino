
const int stepperPinX = 2;
const int dirPinX = 3;
const int stepperPinY = 4;
const int dirPinY = 5;
const int LSX = 6;
const int LSY = 7;
const int IR = 8;

int LSXState = 0;
int LSYState = 0;
int IRState = 0;

const int xDirMultiplier = 1;
const int yDirMultiplier = 1;

int Xspace = 2200;
int Yspace = 2200;

void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, INPUT);
pinMode(7, INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

}

void homeAll(){



}

void xDir(int stepperDir){

stepperDir = stepperDir*xDirMultiplier;

if(stepperDir == 1){

digitalWrite(dirPinX, HIGH);
  
}else{
  digitalWrite(dirPinX, LOW);
}
  
}

void yDir(int stepperDir){

stepperDir = stepperDir*yDirMultiplier;

if(stepperDir == 1){

digitalWrite(dirPinY, HIGH);
  
}else{
  digitalWrite(dirPinY, LOW);
}
  
}
