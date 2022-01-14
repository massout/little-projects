#include <Servo.h>

const int trigPin = 7;
const int echoPin = 6;

Servo motor;

int angle=1, aHandler=1;


void setup(){
	motor.attach(4); 
  	pinMode(trigPin, OUTPUT);
  	pinMode(echoPin, INPUT); 
  	Serial.begin(9600); 
}


void loop(){
  	Serial.print("Angle - Distance: "); 
  	Serial.print(angle);
  	
  	if(angle == 0 || angle == 180) 
    	aHandler *= -1; 

    angle += aHandler; 
  
  	motor.write(angle); 
  	
  	Serial.print(" - "); 
  	
  	digitalWrite(trigPin, HIGH); 
  	delayMicroseconds(50); 
  	digitalWrite(trigPin, LOW);
      	
  	Serial.print(pulseIn(echoPin, HIGH) / 58);
  	Serial.print("\n"); 
}
