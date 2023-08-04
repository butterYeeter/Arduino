void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
int x  = 0;

void loop() {
  // print "Hello There" to the serial monitor:
  Serial.print("Hello There ");
  Serial.println(x);
  // wait one second before printing the next message:
  
  x++;
  if(x ==500){
    x=0;
  }
}
