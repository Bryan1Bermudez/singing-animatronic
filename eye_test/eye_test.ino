#include <FastLED.h>

#define LED_PIN     7


#define ROWS   4
#define COLLUMS   8

#define NUM_LEDS    ROWS * COLLUMS


CRGB B =  CRGB ( 0, 0, 255);

CRGB P =  CRGB ( 106, 11, 65);

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

void setup() {
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);


Serial.begin(9600);


}

void loop() {

      millibegin = millis() - milliend;
      Blink();
  


}



/* void Blink1() {

    delay(500);
    for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = base[f];
      }
    FastLED.show();
      delay(500);

      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink1[f];
      }
      delay(500);
    FastLED.show();

      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
      delay(500);
    FastLED.show();

      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink3[f];
      }
      delay(500);
    FastLED.show();

      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
      delay(500);
    FastLED.show();

      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink1[f];
      }
      delay(500);
    FastLED.show();


} */

void Blink() {

    if(millibegin == 0){
    for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = base[f];
      }
    FastLED.show();
    }
      

    if(millibegin == 200){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink1[f];
      }
      
    FastLED.show();
    }


    if(millibegin == 400){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
    FastLED.show();
        }



    if(millibegin == 600){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink3[f];
      }
    FastLED.show();
    }



      if(millibegin == 800){
      for(int f = 0; f < NUM_LEDS; f ++) {
        leds[f] = blink2[f];
      }
    FastLED.show();
    }


      if(millibegin == 1000){
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
