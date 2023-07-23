
int motorSpeed = 0;



const int led1Pin = 12;
const int led2Pin = 11;
const int led4Pin = 10;
const int led8Pin = 9;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);

pinMode(led1Pin, OUTPUT);
pinMode(led2Pin, OUTPUT);
pinMode(led4Pin, OUTPUT);
pinMode(led8Pin, OUTPUT);

digitalWrite(2, LOW);
digitalWrite(3, LOW);


Serial.println("BOOT");
binEncode(motorSpeed);
}

void loop() {


  
  for(int i = 0; i<200; i++){
digitalWrite(2, LOW);

  
if(motorSpeed==1){
  delay(20);
}
if(motorSpeed==2){
  delay(15);
}
if(motorSpeed==3){
  delay(10);
}
if(motorSpeed==4){
  delay(15);
}
if(motorSpeed == 5){
  delay(10);
  
}
if(motorSpeed == 6){
  delay(8);
}
if(motorSpeed == 7){
  delay(6);
}
if(motorSpeed == 8){
  delay(4);
}
if(motorSpeed == 9){
  delay(2);
}
if(motorSpeed == 10){
  
}
digitalWrite(2, HIGH);


if(motorSpeed>0){
  delay(4);
}
if(motorSpeed==1){
  delay(5);
}
if(motorSpeed==2){
  delay(10);
}
if(motorSpeed==3){
  delay(5);
}
if(motorSpeed==4){
  delay(10);
}
if(motorSpeed == 5){
  delay(10);
  
}
if(motorSpeed == 6){
  delay(8);
}
if(motorSpeed == 7){
  delay(6);
}
if(motorSpeed == 8){
  delay(4);
}
if(motorSpeed == 9){
  delay(2);
}
if(motorSpeed == 10){
  delay(10);
  }

  }

  
  Serial.println(motorSpeed);
  motorSpeed++;
  binEncode(motorSpeed);
}


void binEncode(int input){

 digitalWrite(led8Pin, LOW);
  digitalWrite(led4Pin, LOW);
   digitalWrite(led2Pin, LOW);
    digitalWrite(led1Pin, LOW);
    Serial.println(input);
if(input>=8){
  input -= 8;
  digitalWrite(led8Pin, HIGH);
}
Serial.println(input);
if(input>=4){
  input -= 4;
  digitalWrite(led4Pin, HIGH);
}
Serial.println(input);
if(input>=2){
  input -= 2;
  digitalWrite(led2Pin, HIGH);
}
Serial.println(input);
if(input>=1){
  input -= 1;
  digitalWrite(led1Pin, HIGH);
}



}
