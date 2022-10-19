//Authored by Michael Shepstone on 04/06/2021
const int stepperPinX = 2;
const int dirPinX = 3;
const int stepperPinY = 4;
const int dirPinY = 5;
const int LS1 = 6;
const int LS2 = 7;
const int IR = 8;

int LS1State = 0;
int LS2State = 0;
int IRState = 0;

int distFromHomeY = 0;
int distFromHomeX = 0;

bool Xdir = 0;
bool Ydir=0;

int Ymovetmp = 0;

int Xspace = 2200;
int Yspace = 2200;

int Xinc = 0;

void setup() {
  // put your setup code here, to run once:

pinMode(stepperPinX, OUTPUT);
pinMode(stepperPinY, OUTPUT);
pinMode(dirPinY, OUTPUT);
pinMode(dirPinX, OUTPUT);
pinMode(LS1, INPUT);
pinMode(LS2, INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

  homeSystem();
  delay(1000);
  Ydir = 1;
  updateDir();
for(distFromHomeY; distFromHomeY <= Yspace; distFromHomeY ++){
Ydir = 0;
updateDir();
for(Ymovetmp = 0; Ymovetmp <= 200; Ymovetmp ++){


  distFromHomeY ++;
digitalWrite(stepperPinY, HIGH);
delayMicroseconds (1000);
digitalWrite(stepperPinY, LOW);
delayMicroseconds (1000);

}
Xdir = 0;
updateDir();
for(distFromHomeX; distFromHomeX <= Xspace; distFromHomeX++){
digitalWrite(stepperPinX, HIGH);
delayMicroseconds (1000);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (1000);

}

homeX();
}


}



void updateDir(){
if (Xdir == 0){

  digitalWrite(dirPinX, LOW);



}else{
  digitalWrite(dirPinX, HIGH);
}
if (Ydir == 0){

  digitalWrite(dirPinY, LOW);



}else{
  digitalWrite(dirPinY, HIGH);
}
}

void homeX(){
 Xdir = 1;
 updateDir();
 LS2State = digitalRead(LS2);
while(LS2State == LOW){
LS2State = digitalRead(LS2);

digitalWrite(stepperPinX, HIGH);
delayMicroseconds (500);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (500);

}
distFromHomeX = 0;
 
}



 

void homeSystem(){
    Ydir = 1;
    updateDir();
 LS1State = digitalRead(LS1);
 
while(LS1State == LOW){
  
LS1State = digitalRead(LS1);
digitalWrite(stepperPinY, HIGH);
delayMicroseconds (500);
digitalWrite(stepperPinY, LOW);
delayMicroseconds (500);


 
}

    Xdir = 1;
    updateDir();
 LS2State = digitalRead(LS2);
while(LS2State == LOW){
LS2State = digitalRead(LS2);
digitalWrite(stepperPinX, HIGH);
delayMicroseconds (500);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (500);


 
}
distFromHomeY = 0;
distFromHomeX = 0;

}
