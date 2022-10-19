const int realayPin = 13;
int timer = 0;


void setup() {
  // put your setup code here, to run once:
pinMode(realayPin, OUTPUT);

digitalWrite(realayPin, HIGH);
delay(1000);
digitalWrite(realayPin, LOW);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

for(timer = 0; timer < 10; timer ++){

digitalWrite(realayPin, HIGH);

delay(20000);

digitalWrite(realayPin, LOW);

delay(90000);
}
delay(900000);


  





}
