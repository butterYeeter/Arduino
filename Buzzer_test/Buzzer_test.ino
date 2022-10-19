const int buzzer = 8; //buzzer to arduino pin 9

//This edit was made from within github
void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

void loop(){
startSound();
  
}
void pulseBuzzer(){

tone(buzzer, 329); 
 delay(250);      
noTone(buzzer);
delay(250); 


}

void startSound(){

tone(buzzer, 261.63); 
 delay(100);   
 tone(buzzer, 293.66); 
 delay(100);   
 tone(buzzer, 329.63); 
 delay(100);   
 tone(buzzer, 349.23); 
 delay(100);   
 tone(buzzer, 392); 
 delay(100);   
 tone(buzzer, 440); 
 delay(100);   
 tone(buzzer, 493.88); 
 delay(100);   
 tone(buzzer, 523.25); 
 delay(100);   
    
noTone(buzzer);
delay(500); 


}
void startSound2(){

tone(buzzer, 261.63); 
 delay(200);   

 tone(buzzer, 349.23); 
 delay(500);   
 
 tone(buzzer, 523.25); 
 delay(100);   
    
noTone(buzzer);
delay(500); 


}

void clickBuzzer(){

 tone(buzzer, 1000); 
 delay(100);      
 noTone(buzzer);
   tone(buzzer, 2000); 
  delay(300);   
  noTone(buzzer);   
  tone(buzzer, 3000); 
  delay(150);
  noTone(buzzer);   
  tone(buzzer, 5000); 
  delay(350);        
  noTone(buzzer);     
  delay(1500);        
  

  
}
