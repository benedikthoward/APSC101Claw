/*
Name:			Benedikt Howard
E-mail:			benedikthoward@gmail.com
Student Number:		85748242
Date:			13. Jan, 2023
Purpose:		A simple control flow for a claw powered by an arduino uno
*/

#include <Servo.h>
#include <NewPing.h>

//reference for pin definition
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 8
#define RED_LED 7
#define BLUE_LED 6
#define GREEN_LED 5
#define TIME_1 2
#define TIME_2 3
#define TIME_3 4

// Maximum distance we want to ping for (in centimetres).
#define MAX_DISTANCE 400
#define CLOSING_DISTANCE 10
#define OPENING_TIME 15


//creates objects for the servo and sonar
Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
Serial.begin(9600);
myservo.attach(SERVO_PIN);
	
//defines pins for the LED timers
pinMode(RED_LED, OUTPUT);
pinMode(BLUE_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT);
	
// defines pins for the time function
pinMode(TIME_1,INPUT);
pinMode(TIME_2, INPUT);
pinMode(TIME_3, INPUT);
}

void loop() {
	myservo.write(0);
	int detect = 0;
	int delay_time;
	//detects object
	while(detect < 5){
  		int distance = sonar.ping_cm();
  		if(distance<= CLOSING_DISTANCE&& distance!=0){
    			detect++;
  		}else if(detect >= 0){
    			detect--;
  		}
		Serial.println(distance);
  		delay(100);
	}
	
	// BLINKS to warn of closing
	digitalWrite(GREEN_LED, HIGH);
	delay(1000);
	digitalWrite(GREEN_LED, LOW);
	
	//checks how long the delay should be
	if(digitalRead(TIME_1)==1){
		Serial.println("10s");
		delay_time = 10*1000;
	}else if(digitalRead(TIME_2)==1){
		delay_time = 20*1000;
		Serial.println("20s");
	}else if(digitalRead(TIME_3)==1){
		Serial.println("30s");
		delay_time = 30*1000;
	} else{
		Serial.println("25s");
		delay_time = 25*10000;
	}
	
	//closes
	for(int i = 0; i<=180;i++){
	myservo.write(i);
	delay(3.5);
	}
	delay(500);
	
	//turns the indicator LEDs on
	digitalWrite(GREEN_LED, HIGH);
	digitalWrite(BLUE_LED, HIGH);
	digitalWrite(RED_LED, HIGH);
	
	//delays and LED indicator
	delay(delay_time/4);
	digitalWrite(GREEN_LED, LOW);
	delay(delay_time/4);
	digitalWrite(BLUE_LED, LOW);
	delay(delay_time/4);
	digitalWrite(RED_LED, LOW);
	delay(delay_time/4);
	
	//opens the servo  
	for(int i = 180; i>=0;i--){
		myservo.write(i);
		delay(3.5);
	}
	delay(10000);
}

