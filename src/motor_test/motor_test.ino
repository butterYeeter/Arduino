const int m1b = 4;
const int m1f = 5;
const int m2f = 6;
const int m4 = 7;


void setup() {
  // put your setup code here, to run once:
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);
delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(m1, HIGH);
delay(1000);
digitalWrite(m1, LOW);
delay(2000);

digitalWrite(m2, HIGH);
delay(1000);
digitalWrite(m2, LOW);
delay(2000);

digitalWrite(m3, HIGH);
delay(1000);
digitalWrite(m3, LOW);
delay(2000);

digitalWrite(m4, HIGH);
delay(1000);
digitalWrite(m4, LOW);
delay(5000);


}
