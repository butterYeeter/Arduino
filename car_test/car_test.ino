const int m1 = 4;
const int m2 = 5;
const int m3 = 6;
const int m4 = 7;

const int trigPin = 3;
const int echoPin = 2;



void setup() {
  // put your setup code here, to run once:
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  
delay(8000);
}
void loop() {
  // put your main code here, to run repeatedly:

accelerate(255);


}




void travel(int maxSpeed, int duration){
analogWrite(m1, maxSpeed);
analogWrite(m2, maxSpeed);
analogWrite(m3, maxSpeed);
analogWrite(m4, maxSpeed);

delay(duration*100);

}

void turnLeft(int maxSpeed, int duration){
analogWrite(m1, maxSpeed);
analogWrite(m2, 0);
analogWrite(m3, 0);
analogWrite(m4, maxSpeed);

delay(duration*100);

}

void turnRight(int maxSpeed, int duration){
analogWrite(m1, 0);
analogWrite(m2, maxSpeed);
analogWrite(m3, maxSpeed);
analogWrite(m4, 0);

delay(duration*100);

}

void accelerate(int maxSpeed){

digitalWrite(m1, LOW);
digitalWrite(m2, LOW);
digitalWrite(m3, LOW);
digitalWrite(m4, LOW);

for(int i = 0; i<maxSpeed; i++){
  analogWrite(m1, i);
 
  analogWrite(m4, i);

delay(15);



}


}
