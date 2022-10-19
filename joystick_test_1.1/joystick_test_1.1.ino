
const int xPulPin = 3;
const int xDirPin = 4;
const int yPulPin = 5;
const int yDirPin = 6;
const int zPulPin = 7;
const int zDirPin = 8;

const int waypt = 10;
const int up = 11;
const int dn = 12;



int X, Y;
int Xpos = 0;
int Ypos = 0;
int Zpos = 0;

void setup() {
  // put your setup code here, to run once:

pinMode(xPulPin, OUTPUT);
pinMode(xDirPin, OUTPUT);
pinMode(yPulPin, OUTPUT);
pinMode(yDirPin, OUTPUT);
pinMode(zPulPin, OUTPUT);
pinMode(zDirPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Y = analogRead(A0)/10-50;
X = analogRead(A1)/10-50;

if(digitalRead(up) == HIGH){

  
  for (int i = 0; i<79; i++){
    delayMicroseconds(1000);
digitalWrite(zDirPin, HIGH);
digitalWrite(zPulPin, HIGH);
Zpos++;
delayMicroseconds(1000);
digitalWrite(zPulPin, LOW);
    
  }
}

if(X > 7){
digitalWrite(xDirPin, HIGH);
digitalWrite(xPulPin, HIGH);
Xpos++;

}
else if(X < -7){
  X = X*-1;
digitalWrite(xDirPin, LOW);
digitalWrite(xPulPin, HIGH);
Xpos--;
 
}

if(Y > 7){
digitalWrite(yDirPin, HIGH);
digitalWrite(yPulPin, HIGH);
Ypos++;
  
}
else if(Y < -7){
  Y = Y*-1;
digitalWrite(yDirPin, LOW);
digitalWrite(yPulPin, HIGH);
Ypos--;
 
}
delayMicroseconds(550-Y*10);
digitalWrite(xPulPin, LOW);
digitalWrite(yPulPin, LOW);
  delayMicroseconds(550-Y*10);



Serial.println();
}

void stepMotor(){
 




}
