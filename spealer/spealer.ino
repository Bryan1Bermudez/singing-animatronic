///              MP3 PLAYER PROJECT
/// http://educ8s.tv/arduino-mp3-player/
//////////////////////////////////////////


#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

#define CLK 2
#define DT 3
#define SW 4

#define LED_PIN 13

#include <Servo.h> 


#include <FastLED.h>

#define LED_PIN     7


#define ROWS   4
#define COLLUMS   8

#define NUM_LEDS    ROWS * COLLUMS

CRGB B =  CRGB ( 0, 0, 105);

CRGB P =  CRGB ( 56, 5, 15);

CRGB F =  CRGB ( 0, 0, 0);

CRGB base [NUM_LEDS] = {
  B,B,B,B
  ,B,P,P,B
  ,B,B,B,B,
  F,F,F,F,
  F,F,F,F,
  B,B,B,B,
  B,P,P,B,
  B,B,B,B

};

CRGB blink1 [NUM_LEDS] = {
  B,B,B,F,
  F,B,P,B,
  B,B,B,F,
  F,F,F,F,
  F,F,F,F,
  F,B,B,B,
  B,P,B,F,
  F,B,B,B,

};


CRGB blink2 [NUM_LEDS] = {
  B,B,F,F,
  F,F,B,P,
  B,B,F,F,
  F,F,F,F,
  F,F,F,F,
  F,F,B,B,
  P,B,F,F,
  F,F,B,B,


};

CRGB blink3 [NUM_LEDS] = {
  B,F,F,F,
  F,F,F,B,
  B,F,F,F,
  F,F,F,F,
  F,F,F,F,
  F,F,F,B,
  B,F,F,F,
  F,F,F,B,
};
//Blink Animation
#define BLINKFRAMES   8
CRGB blinkAni [NUM_LEDS][BLINKFRAMES] = {
  base,blink1,blink2,blink3,blink2,blink3,blink1,base

};


CRGB leds[NUM_LEDS];


#define FIVE 5000   

#define BLINK 8000   
int del = FIVE;

int millibegin = 0;
int milliend = 0;








Servo mouth;


int buttonNext = 8;
int buttonPrevious = 6;
boolean isPlaying = false;

int potPin = A0; 
int potVal = 0;



int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

int volume = 10;
int preServo = 0;





void setup () {

pinMode(LED_PIN,OUTPUT);


	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

  mouth.attach(13);


   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);


  


pinMode(buttonNext, INPUT);
digitalWrite(buttonNext,HIGH);
pinMode(buttonPrevious, INPUT);
digitalWrite(buttonPrevious,HIGH);

mySerial.begin (9600);
Serial.begin(9600);
delay(100);
playFirst();
isPlaying = true;

lastStateCLK = digitalRead(CLK);

	attachInterrupt(0, updateEncoder, CHANGE);
	attachInterrupt(1, updateEncoder, CHANGE);


  digitalWrite(13, HIGH);   
  delay(100);              
  digitalWrite(13, LOW);   
  delay(100);    




}



void loop () { 

currentStateCLK = digitalRead(CLK);

pauseButton();

setVolume(volume);


 if (digitalRead(buttonNext) != ACTIVATED && digitalRead(buttonPrevious) != ACTIVATED)
  {

      Shuffle();
    
  }

 else if (digitalRead(buttonNext) != ACTIVATED)
  {
    if(isPlaying)
    {
      playNext();
    }
  }
   else if (digitalRead(buttonPrevious) != ACTIVATED)
  {
    if(isPlaying)
    {
      playPrevious();
    }
  }








potVal = analogRead(potPin) ;

Serial.println(potVal);

if((((potVal * potVal)/potVal) > (550 + (volume * 2)  )  ) && isPlaying) {

mouth.write(470);
preServo = 380;
delay(10);
Serial.println("open");
} else if(preServo != 80 && isPlaying){
  
  if(preServo < 80) {
    preServo = preServo + 20;
    

  } 
  else if(preServo > 80)
  {
    preServo  = preServo - 20;
    
  }
    mouth.write(preServo);
    
Serial.println("closed");
 delay(10);
} else {

  mouth.write(0);
}




delay(10);

    millibegin = millis() - milliend;
     Blink();




  


}

void updateEncoder(){
	// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
      if(volume == 30){
        volume = 30;
      } else {
        volume ++;
      }

		} else {
			// Encoder is rotating CW so increment
      if(volume == 0){
        volume = 0;
      } else {
        volume --;
      }
			

	
		}
	}
  		Serial.print(" | Counter: ");
		Serial.println(volume);

  lastStateCLK = currentStateCLK;

}



void pauseButton()
{

int btnState = digitalRead(SW);




	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50 && isPlaying) {
			pause();
      isPlaying = false;
		}
    		else if (millis() - lastButtonPress > 50 && !isPlaying) {
        isPlaying = true;
			play();
    
		}
    		// Remember last button press event
		lastButtonPress = millis();
	}
  delay(1);


}

void Shuffle() 
{
  int rand = random(0,42);
  for(int i = 0; i < rand; i ++) {
    playNext();
  }

}


void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(volume);
  delay(500);
  execute_CMD(0x11,0,1); 
  delay(500);
}

void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}

void playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
}

void playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(20);
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command line to the module
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}




void Blink() {

    if(millibegin  < 200){
    for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = base[f];
      }
    FastLED.show();
    }
      

    if(millibegin > 200 &&  millibegin <400){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink1[f];
      }
      
    FastLED.show();
    }


    if(millibegin > 400 &&  millibegin <600){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
    FastLED.show();
        }



    if(millibegin > 600 &&  millibegin <800){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink3[f];
      }
    FastLED.show();
    }



      if(millibegin > 800 &&  millibegin <1000){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
    FastLED.show();
    }


      if(millibegin > 1000 &&  millibegin < 1200){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink1[f];
      }
    FastLED.show();
      }

      if(millibegin >= 1200){
        milliend = millis() + 3000;

          for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = base[f];
      }
          FastLED.show();
      }

}


