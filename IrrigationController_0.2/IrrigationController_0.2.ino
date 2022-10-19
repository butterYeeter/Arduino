

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
#include <SPI.h>
#include <EEPROM.h>
#include <virtuabotixRTC.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Encoder myEnc(5, 6);

//Wiring SCLK -> 7, I/O -> 8, CE -> 9
//Or CLK -> 7, DAT -> 8, Reset -> 9
 
virtuabotixRTC myRTC(7, 8, 9); //If you change the wiring change the pins here also
 
int setupmatrixlocation = 100;
int editing = 0;
int oldPosition  = 0;
int newPosition = 0;
int pos = 0;
int currentScreen = 0;
int portToEdit;
int editMode;
 const int PROGMEM BtnPin = PD4;
const int PROGMEM checkBoxW = 9;
const int PROGMEM checkBoxH = 9;

const int PROGMEM RegData = 12;
const int PROGMEM RegClk = 11;
const int PROGMEM RegLatch = 10;

char *dayNames [7]  = {"Monday",  "Tuesday",  "Wednesday",  "Thursday",  "Friday",  "Saturday",  "Sunday"};


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

int stateMatrix [8]; //={0,0,0,0,0,0,0};
int oldstateMatrix [8] = {0,0,0,0,0,0,0,0};

/*setup matrix format is as follows:
 * setupMatrix [relayNumber] [data searched for]
 * {{ Datatype (0 = blank, 1 = enable at time, 2 = toggle every time)
 * 0   Enable hour
 * 1   Enable Minute
 * 2   Disable hour
 * 3   Disable minute
 * 4   enable wait hour
 * 5   enable wait minute
 * 6   disable wait hour
 * 7   disable wait minute
 * 8   enable day mon
 * 9   enableday tue
 * 10   enableday wed
 * 11   enableday thurs
 * 12   enableday fri
 * 13   enableday sat
 * 14   enableday sun
 * }}
 * 
 */
int setupMatrix [8][15];

int minute;
int minuteOld = 0;
int hour;
int day = 0;
int dayold = 0;
int dayofweek = 1;
void setup() {

for(int x = 0; x<8; x++){

stateMatrix[x] = EEPROM.read(x);

  
}

  Serial.begin(9600);

  pinMode(RegData, OUTPUT);
pinMode(RegClk, OUTPUT);
pinMode(RegLatch, OUTPUT);


  

    
display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  //SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
   


  

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(100);
  display.setTextColor(WHITE);
  UpdateMenu();

}



void loop() {
  ReadEncoder();
  checkBtn();
  
UpdateRelay();
GetTime();
  
 // delay(100);
}

void CheckLogic(){
for(int x = 0; x<8; x++){
if(setupMatrix[x][0] == 1){
if(setupMatrix[x][1] == hour and setupMatrix[x][2] == minute and setupMatrix[x][dayofweek+8] == 1){
 stateMatrix[x] = 1; 
}
if(setupMatrix[x][3] == hour and setupMatrix[x][4] == minute ){
 stateMatrix[x] = 0; 
}
}
if(setupMatrix[x][0] == 2){
if(setupMatrix[x][1] == hour and setupMatrix[x][2] == minute and setupMatrix[x][dayofweek+8] == 1){
 stateMatrix[x] = 1; 
 setupMatrix[x][1] = setupMatrix[x][1] + setupMatrix[x][4];
 setupMatrix[x][2] = setupMatrix[x][2] + setupMatrix[x][5];

 if(setupMatrix[x][1]>=24){
  setupMatrix[x][1]=setupMatrix[x][1]-24;
 }
 if(setupMatrix[x][2]>=60){
  setupMatrix[x][2]=setupMatrix[x][2]-60;
 }
}
if(setupMatrix[x][3] == hour and setupMatrix[x][4] == minute  ){
 stateMatrix[x] = 0;
 setupMatrix[x][3] = setupMatrix[x][3] + setupMatrix[x][6];
 setupMatrix[x][4] = setupMatrix[x][4] + setupMatrix[x][7]; 
}

if(setupMatrix[x][3]>=24){
  setupMatrix[x][3]=setupMatrix[x][3]-24;
 }
 if(setupMatrix[x][4]>=60){
  setupMatrix[x][4]=setupMatrix[x][4]-60;
 }

  
}
}

  
}

void GetTime(){

  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();
 
// Start printing elements as individuals
 /*Serial.print("Current Date / Time: ");
 Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print(" ");
 Serial.print(myRTC.hours);
 Serial.print(":");
 Serial.print(myRTC.minutes);
 Serial.print(":");
 Serial.println(myRTC.seconds);
 */
minute = myRTC.minutes;
hour = myRTC.hours;
//day = myRTC.dayofmonth;

if(dayold!= day){
dayofweek++;

if(dayofweek == 8){
  dayofweek = 1;
}
}
dayold = day;
dayofweek = myRTC.dayofweek;
if(minute!=minuteOld){
  delay(100);
UpdateMenu();
delay(100);
minuteOld = minute;
}

}


void checkBtn(){

if(digitalRead(BtnPin)==LOW){

if (currentScreen == 0){
switch (pos){

case 0:
currentScreen = 1;
break;
case 1:
currentScreen = 2;

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
//break;
delay(500);}
}


if(digitalRead(BtnPin)==LOW){
 if(currentScreen == 2){
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

}}


if(digitalRead(BtnPin)==LOW){
 if(currentScreen == 1){
  if (editing == 0){
if (pos == 0){
  currentScreen = 0;
}
if (pos == 1){
  editing = 1;
}

if (pos == 2){
  editing = 2;
}

pos = 0;
  myEnc.write(0);

 }else{
  editing = 0;
  
  
 }


pos = 0;
  myEnc.write(0);
UpdateMenu();
 delay(300);

}}

if(digitalRead(BtnPin)==LOW){
 if(currentScreen == 3){
if (pos >= 0){
switch (pos){

case 0:
currentScreen = 4;
break;
case 1:
currentScreen = 5;

pos = 0;

break;
case 2:
//currentScreen = 3;

//reset device

  break;

  
}

}
pos = 0;
myEnc.write(0);
UpdateMenu();
 
delay(500);
}}


if(digitalRead(BtnPin)==LOW){
 if(currentScreen == 4){
currentScreen = 3;





UpdateMenu();
 
delay(500);
}}




 if(digitalRead(BtnPin)==LOW){


  
 if(currentScreen == 5){
if (editing ==0){
if (pos == 0){
  currentScreen = 3;
  delay(500);
}
if(pos ==1){

if (editing == 1){
  editing = 0;
}else{
editing = 1;
pos = 0;
myEnc.write(0);
}
  delay(500);
}

if(pos ==2){

if (editing == 2){
  editing = 0;
}else{
editing = 2;
pos = 0;
myEnc.write(0);
}
  delay(500);
}
if(pos ==3){

if (editing == 3){
  editing = 0;
}else{
editing = 3;
pos = 0;
myEnc.write(0);
}
  delay(500);
}
if(pos ==4){

myRTC.setDS1302Time(00, minute, hour, dayofweek, 1, 1, 2021);
  delay(500);
}

}else{
 if(digitalRead(BtnPin)==LOW){
if (editing == 1 ){
  hour = pos;
  editing = 0;
  myRTC.setDS1302Time(00, minute, hour, dayofweek, 1, 1, 2021);
  
}
if (editing == 2 ){
  minute = pos;
  editing = 0;
  myRTC.setDS1302Time(00, minute, hour, dayofweek, 1, 1, 2021);
  
}
if (editing == 3 ){
  dayofweek = pos;
  editing = 0;
  myRTC.setDS1302Time(00, minute, hour, dayofweek, 1, 1, 2021);
  
}delay(500);
 }

}

UpdateMenu();
 

}}

   
}

void ReadEncoder(){
newPosition = myEnc.read();
 
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
display.print(F("Setup  <--"));
display.setCursor(10,20);
display.print(F("Manaul Control  "));
display.setCursor(10,40);
display.print(F("Other "));

    display.display();
break;
case 1:
display.setCursor(10,0);
display.print(F("Manaul Control  <--"));
display.setCursor(10,20);
display.print(F("Other "));
display.setCursor(10,40);
display.print(F("Setup  "));
//displayStats

    display.display();
break;
case 2:
display.setCursor(10,0);
display.print(F("Other  <--"));
display.setCursor(10,20);

display.print(F("Setup  "));
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


else if (currentScreen == 1){
if (editing == 0){
display.setCursor(0,0);
display.setTextSize(0.2);
if (pos == -1){

  //fix it
}
display.print(F("Back"));
if(pos == 0){

  display.print(F("<--"));
}


display.setCursor(5,8);
display.print(F("Editing Port:"));
display.print(portToEdit);
if(pos == 1){

  display.print(F("<--"));
}
display.setCursor(5,18);
display.print(F("Control Mode:"));
display.print(editMode);
if(pos == 2){

  display.print(F("<--"));
}
if(editMode == 1){
display.setCursor(5,28);
display.print(F("On At:"));
display.setCursor(5,36);
display.print(F("Off At:"));
display.setCursor(30,40);

int loops = 0;
for(int i = 5; i<=95; i=i+15){


  display.drawBitmap(
     i,
     56,
    checkBox_bmp, checkBoxW, checkBoxH, 1);
display.setCursor(i+2,46);
display.print(dayNames[loops][0]);
    loops++;
}}
}





if (editing == 1){
display.setCursor(0,0);
display.setTextSize(0.2);
portToEdit = pos;
if (pos == -1){

  pos = 8;
  myEnc.write(32);
}
display.print(F("Back"));



display.setCursor(5,8);
display.print(F("Editing Port:"));
display.print(portToEdit);

if (pos == 9){

  pos = 0;
  myEnc.write(0);
}
}
if (editing == 2){
display.setCursor(0,0);
display.setTextSize(0.2);
editMode = pos;
if (pos == -1){

  pos = 2;
  myEnc.write(8);
}
display.print(F("Back"));



display.setCursor(5,16);
display.print(F("Control Mode:"));
display.print(editMode);

if (pos == 3){

  pos = 0;
  myEnc.write(0);
}
}


  
}
else if (currentScreen == 2){
  

  
  switch (pos){

  case -2:
  myEnc.write(28);
pos = 7;

case -1:
display.setCursor(0,0);
display.print(F("Back <-- "));

break;
case 8:
   myEnc.write(0);
  pos = 0;
  
  break;
  }
  



display.setCursor(0,0);
display.print(F("Back "));
display.setCursor(20,17);
display.print(F("MANAUL CONTROL"));
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
display.print(F("!"));

display.display();
}else if (currentScreen == 3){
if (pos == -1){
  pos = 3;
  myEnc.write(12);
}
else if (pos ==0){
display.setCursor(10,0);
display.print(F("Display Clock  <--"));
display.setCursor(10,20);

display.print(F("Set Clock  "));
display.setCursor(10,40);

display.print(F("Reset device"));
    display.display();

    
}else if (pos == 1){
display.setCursor(10,0);
display.print(F("Set Clock <-- "));
display.setCursor(10,20);
display.print(F("Reset device"));

display.setCursor(10,40);
display.print(F("Back"));

    display.display();

  
}else if(pos == 2){
display.setCursor(10,0);

display.print(F("Reset device <--"));
display.setCursor(10,20);

display.print(F("Back "));
display.setCursor(10,40);

display.print(F("Display Clock  "));
    display.display();
  
}else if (pos == 3){
  display.setCursor(10,0);
display.print(F("Back <--"));
display.setCursor(10,20);

display.print(F("Display Clock "));
display.setCursor(10,40);

display.print(F("Set Clock "));
    display.display();

  
}  
  else{


  pos = 0;
  myEnc.write(0);
}


}else if (currentScreen == 4){

  display.setCursor(0,0);
display.print(F("Back "));

display.setCursor(20,20);
display.setTextSize(3);

if(hour<10){
  display.print(F("0"));
}

display.print(hour);
display.print(F(":"));
if(minute<10){
  display.print(F("0"));
}
display.print(minute);

display.setTextSize(1);
display.setCursor(20,45);

  
int displayletter = dayofweek-1;
Serial.println(int(dayofweek-1));
delay(100);
 display.print(dayNames[dayofweek-1]); 
 delay(10);
 

}else if (currentScreen == 5){
if(editing == 0){
  display.setCursor(0,0);
display.print(F("Back "));
if (pos == -1){
  pos = 4;
  myEnc.write(16);
}
if(pos == 0){

   display.setCursor(0,0);
display.print(F("Back <--"));
}
display.setCursor(20,20);
display.setTextSize(3);

if(hour<10){
  display.print(F("0"));
}

display.print(hour);
display.print(F(":"));
if(minute<10){
  display.print(F("0"));
}
display.print(minute);

display.setTextSize(1);
display.setCursor(20,45);

if (pos == 1){
display.drawLine(20, 42, 52, 42, WHITE);
}

if (pos == 2){
display.drawLine(74, 42, 108, 42, WHITE);
}
  
int displayletter = dayofweek-1;
Serial.println(int(dayofweek-1));
display.setTextSize(1);
display.setCursor(20,45);
 display.print(dayNames[dayofweek-1]); 
 delay(10);

 if (pos == 3){
display.print(" <--");
 }
display.setCursor(100,0);
display.print(F("Save "));

 if (pos == 4){
  display.setCursor(80,0);
  display.print(F("-->"));
 }

 if (pos ==0){
  
 }
 if (pos>4){
  pos = 0;
  myEnc.write(0);
 }


}

if(editing == 1){
hour = pos;
if(pos == -1){
  pos = 23;
  myEnc.write(92);
}
if(pos == 24){
  pos = 0;
  myEnc.write(0);
}
  display.setCursor(20,20);
display.setTextSize(3);

if(hour<10){
  display.print(F("0"));
}

display.print(hour);
display.print(F(":"));
if(minute<10){
  display.print(F("0"));
}
display.print(minute);

display.setTextSize(1);
}
if(editing == 2){
minute = pos;
if(pos == -1){
  pos = 59;
  myEnc.write(236);
}
if(pos == 60){
  pos = 0;
  myEnc.write(0);
}
  display.setCursor(20,20);
display.setTextSize(3);

if(hour<10){
  display.print(F("0"));
}

display.print(hour);
display.print(F(":"));
if(minute<10){
  display.print(F("0"));
}
display.print(minute);

display.setTextSize(1);
}

if(editing == 3){
dayofweek = pos+1;
if(pos == -1){
  pos = 6;
  myEnc.write(24);
}
if(pos == 7){
  pos = 0;
  myEnc.write(0);
}
display.setTextSize(1);
display.setCursor(20,45);
 display.print(dayNames[dayofweek-1]);
}
 
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

}else{

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

for(int x = 0; x<=7; x++){
oldstateMatrix[x] = stateMatrix[x];
diff = 0;
}
}

for(int x = 0; x<8; x++){

 EEPROM.update(x, stateMatrix[x]);

  
}
}
