//Variables for all our components and component states
//Buttons
int Butt=2;
int Buttstate;
int laststate=0;
int pButt=7;
int pButtState;
int pLastState=0;
//Piezo
int pie=3;
//PIR sensor
int PIR=5;
int PIRstate;
//LED
int LEDS=4;
//Servo & Servo library
#include<Servo.h>
Servo motor;
//LCD & LCD library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
//Photoresistor
int pRest=A0;
int pRestVal;

void setup()
{
  //LCD setup
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.display();
  //Button setup
  pinMode(Butt,INPUT);
  pinMode(pButt,INPUT);
  //Piezo Setup
  pinMode(pie, OUTPUT);
  //PIR setup
  pinMode(PIR,INPUT);
  //Motor setup
  motor.attach(6);
  //Phototransistor setup
  pinMode(pRest,INPUT);
  //Begin Serial Monitor
  Serial.begin(9600);
  
}

void loop()
{
  //Clear LCD, motor, & LEDs after each time.
  lcd.clear();
  motor.write(0);
  digitalWrite(LEDS,LOW);

  //Read button and PIR
  Buttstate=digitalRead(Butt);
  PIRstate=digitalRead(PIR);
  Serial.println(Buttstate);
  pButtState=digitalRead(pButt);
  
  //Read phototransistor and its button
  pRestVal=analogRead(pRest);
  Serial.print("PhotoresistorVal= ");
  Serial.println(pRestVal);
  Serial.print("pButt= ");
  Serial.println(pButtState);
  
  //if phototransistor button is pressed
  if(pButtState==HIGH){
    pLastState=pButtState;
    pLastState=1;
  }//if light is bright = no food is blocking the light`
  if(pLastState==1 && pRestVal>=30){
    lcd.setCursor(0,-1);
    lcd.print("Food is low!");
    delay(1000);
    pLastState=0;
  }//if light is dark = food is blocking the light
  else if (pLastState==1 && pRestVal<30){
    lcd.setCursor(0,-1);
    lcd.print("Food is enough.");
    delay(1000);
    pLastState=0;
  }
  
  //If button is pressed
  if(Buttstate==HIGH){
    laststate=Buttstate;
    tone(pie,659);// melody
    delay(200);
    tone(pie,622);
    delay(200);
    tone(pie,659);
    delay(200);
    tone(pie,622);
    delay(200);
    tone(pie,659);
    delay(200);
    tone(pie,494);
    delay(200);
    tone(pie,587);
    delay(200);
    tone(pie,523);
    delay(200);
    tone(pie,440);
    delay(200);
    noTone(pie);
  	Serial.println(PIRstate);
    laststate=1;
  }
  //If PIR is sensed after the button is pressed
  if(laststate==1&&PIRstate==HIGH){
    	motor.write(100);
    	delay(120);
    	LEDBLINK();
    	LCD();
    	laststate=0;
  }	
}
//Blinking LEDs function
void LEDBLINK(){
	digitalWrite(LEDS,HIGH);
  	delay(350);
  	digitalWrite(LEDS,LOW);
  	delay(350);
  	digitalWrite(LEDS,HIGH);	
  	delay(350);
  	digitalWrite(LEDS,LOW);
}

//LCD I2C function
void LCD(){
  	lcd.setCursor(0,0);//Set cursor to character 2 on line 0
  	lcd.print("Yum!");
  	Serial.println("LCD WORKING");
  	delay(1000);
}
