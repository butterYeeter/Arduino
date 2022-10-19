

const int stepperPinY = 2;
const int dirPinY = 3;
const int stepperPinX = 4;
const int dirPinX = 5;
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

int Xspace = 4000;
int Yspace = 4000;

int Xinc = 0;

void setup() {
  // put your setup code here, to run once:

pinMode(stepperPin, OUTPUT);
pinMode(dirPin, OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

  homeSystem();
  Ydir = 1;
  
for(distFromHomeY; distfromHomeY <= Yspace; distFromHomeY ++;){

for(distFromHomeY; distfromHomeY <= 200; distFromHomeY ++;){
digitalWrite(stepperPinY, HIGH);
delayMicroseconds (1000);
digitalWrite(stepperPinY, LOW);
delayMicroseconds (1000);

}
Xdir = 0;
for(distFromHomeX; distfromHomeY <= Xspace; distFromHomeX +Xinc;){
digitalWrite(stepperPinX, HIGH);
delayMicroseconds (1000);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (1000);

}

homeX();
}


}





void homeX(){
 Xdir = 1;
while(digitalRead(LS2)==LOW){

digitalWrite(stepperPinX, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (350);

}
distFromHomeX = 0;
  
}



  

void homeSystem(){
    Ydir = 0;
while(digitalRead(LS1)==LOW){

digitalWrite(stepperPinY, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPinY, LOW);
delayMicroseconds (350);


  
}

    Xdir = 1;
while(digitalRead(LS2)==LOW){

digitalWrite(stepperPinX, HIGH);
delayMicroseconds (350);
digitalWrite(stepperPinX, LOW);
delayMicroseconds (350);


  
}
distFromHomeY = 0;
distFromHomeX = 0;

}
