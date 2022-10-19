/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Encoder myEnc(5, 6);
//   avoid using pins with LEDs attached

int oldPosition  = 0;
int newPosition = 0;
int pos = 0;
int currentScreen = 0;
const int BtnPin = PD4;
int checkBoxW = 9;
int checkBoxH = 9;

const int RegData = 12;
const int RegClk = 11;
const int RegLatch = 10;

int diff = 0;

static const unsigned char PROGMEM checkBox_bmp [] = {
0b00000000, 0b0,
0b00000000, 0b0,
0b00000000, 0b0,
0b00111110, 0b0,
0b00100010, 0b0,
0b00100010, 0b0,
0b00100010, 0b0,
0b00111110, 0b0,
0b00000000, 0b0


};

static const unsigned char PROGMEM checkedBox_bmp [] = {
0b00000000, 0b0,
0b00000000, 0b1,
0b00000001, 0b1,
0b00111111, 0b1,
0b11100111, 0b0,
0b01111110, 0b0,
0b00111010, 0b0,
0b00111110, 0b0,
0b00000000, 0b0


};

int stateMatrix [8]={0,0,0,0,0,0,0};
int oldstateMatrix [8];


void setup() {
  Serial.begin(9600);

  pinMode(RegData, OUTPUT);
pinMode(RegClk, OUTPUT);
pinMode(RegLatch, OUTPUT);


  Serial.println("Basic Encoder Test:");

    
display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  //SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println("Initialised Display");


  

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  display.setTextColor(WHITE);
  UpdateMenu();
    Serial.println("Initialisation Complete");
}



void loop() {
  ReadEncoder();
  checkBtn();
  
UpdateRelay();

for(int x = 0; x<=7; x++){
Serial.print(stateMatrix[x]);
Serial.print(" ");
}
Serial.println(" ");
  for(int x = 0; x<=7; x++){
Serial.print(oldstateMatrix[x]);
Serial.print(" ");
}

  
 // delay(100);
}
void checkBtn(){

if(digitalRead(BtnPin)==LOW){
  Serial.print("LOW");
if (currentScreen == 0){
switch (pos){

case 0:
currentScreen = 1;
break;
case 1:
currentScreen = 2;
delay(600);
pos = 0;
break;
case 2:
currentScreen = 3;

//reset device

  break;

  
}
 pos = 0;
myEnc.write(0);

UpdateMenu();
break;
}else if(currentScreen == 2);
if (pos >= 0){
if(stateMatrix[pos]==0){

  stateMatrix[pos]=1;
}else{

  stateMatrix[pos]=0;
}
}

if (pos == -1){

  currentScreen = 0;
   pos = 0;
myEnc.write(0);
}




UpdateMenu();
 delay(300);

}


 
}
void ReadEncoder(){
newPosition = myEnc.read();
  Serial.println(pos);
  if (newPosition/4 != oldPosition/4) {
    oldPosition = newPosition;
  
    pos = newPosition/4;
    //delay(200);
    //oldPosition = 0;
    //newPosition = 0;
UpdateMenu();
  }
  
  
  }
  

  void UpdateMenu(){
   
  
    display.setTextSize(1);
  display.clearDisplay();
  
  if (currentScreen == 0){
switch (pos){
case -1:
myEnc.write(8);
pos = 2;
case 0:
display.setCursor(10,0);
//display.drawPixel(11,11, WHITE);
display.print("Setup  <--");
display.setCursor(10,20);
display.print(F("Display Statistics  "));
display.setCursor(10,40);
display.print("Reset Device ");

    display.display();
break;
case 1:
display.setCursor(10,0);
display.print(F("Manaul Control  <--"));
display.setCursor(10,20);
display.print("Reset Device ");
display.setCursor(10,40);
display.print("Setup  ");
//displayStats

    display.display();
break;
case 2:
display.setCursor(10,0);
display.print("Reset Device  <--");
display.setCursor(10,20);

display.print("Setup  ");
display.setCursor(10,40);

display.print(F("Display Statistics  "));
    display.display();

//reset device
break;
  case 3:
  pos = 0;
  myEnc.write(0);
  break;
  default:
  pos = 0;
  break;
}}
else if (currentScreen == 2){
  

  
  switch (pos){

  case -2:
  myEnc.write(28);
pos = 7;

case -1:
display.setCursor(0,0);
display.print("Back <-- ");

break;
case 8:
   myEnc.write(0);
  pos = 0;
  Serial.print("default");
  break;
  }
  



display.setCursor(0,0);
display.print("Back ");
display.setCursor(20,17);
display.print("MANAUL CONTROL");
int loopruns = 0;
for(int i = 5; i<=110; i=i+15){

if(stateMatrix[loopruns]==1){
  display.drawBitmap(
     i,
     40,
    checkedBox_bmp, checkBoxW, checkBoxH, 1);
}else{

  display.drawBitmap(
     i,
     40,
    checkBox_bmp, checkBoxW, checkBoxH, 1);
}

loopruns++;
    
}

display.setCursor(pos*15+7,48);
display.print("!");

display.display();









}

  


display.display();
}


void UpdateRelay(){
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
//  Serial.println("HIGH");
}else{
//Serial.println("LOW");
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
oldstateMatrix[x] = stateMatrix[x];
diff = 0;
}
}

}
