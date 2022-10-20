const int m1 = 4;
const int m2 = 5;
const int m3 = 6;
const int m4 = 7;


void setup() {
  // put your setup code here, to run once:
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);
delay(8000);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(m4, HIGH);

digitalWrite(m1, HIGH);
}
