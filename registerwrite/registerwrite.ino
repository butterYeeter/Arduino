
int stateMatrix [8] = {0,0,0,0,0,1,0,1};
int oldstateMatrix [8] = {0,1,0,0,0,0,0,0};
int diff = 0;
const int RegData = 12;
const int RegClk = 11;
const int RegLatch = 10;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(RegData, OUTPUT);
pinMode(RegClk, OUTPUT);
pinMode(RegLatch, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

for (int x = 0; x<=7; x++){
if(stateMatrix[x] != oldstateMatrix[x]){
  diff++;
}
}

  if(diff != 0){
for (int x = 0; x<=7; x++){
delay(10);
int currentReg = stateMatrix[x];
if( currentReg== 1){
digitalWrite(RegData, HIGH);
  Serial.println("HIGH");
}else{
Serial.println("LOW");
  digitalWrite(RegData, LOW);
}
delay(10);
digitalWrite(RegClk, HIGH);

delay(10);
digitalWrite(RegClk, LOW);

  delay(10);
digitalWrite(RegData, LOW);
}



delay(10);
digitalWrite(RegLatch, LOW);

delay(10);
digitalWrite(RegLatch, HIGH);
Serial.println("Write to register");
for(int x = 0; x<=7; x++){
//oldstateMatrix[x] = stateMatrix[x];
diff = 0;
}
}

}
