void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int btnState = digitalRead(PD4);

Serial.println(digitalRead(PD4));
if (btnState == HIGH){


Serial.println("HIGH");
}else{

  Serial.println("LOW");
}
}
