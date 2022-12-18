
#include <ESP32Servo.h>

Servo myservo;  

int pos = 0;    

void setup() {
  myservo.attach(15);  
  Serial.begin(115200);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              
    delay(15); 
    Serial.println(pos);                      
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);            
    delay(15);
    Serial.println(pos);                   
  }
}