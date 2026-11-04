#include <FastLED.h>

#define LED_PIN     7


#define ROWS   4
#define COLLUMS   8

#define NUM_LEDS    ROWS * COLLUMS


CRGB B =  CRGB ( 0, 0, 255);

CRGB P =  CRGB ( 106, 11, 65);

CRGB OF =  CRGB ( 0, 0, 0);

CRGB base    [ROWS][COLLUMS] = {
       {B,B,B,OF,OF,B,B,B},
       {B,P,B,OF,OF,B,P,B},
       {B,P,B,OF,OF,B,P,B},
       {B,B,B,OF,OF,P,B,B}
} ;

CRGB BLI    [ROWS][COLLUMS] = {
       {B,B,B,OF,OF,B,B,B},
       {B,P,B,OF,OF,B,P,B},
       {B,P,B,OF,OF,B,P,B},
       {B,B,B,OF,OF,P,B,B}
} ;

CRGB current [NUM_LEDS];
CRGB leds[NUM_LEDS];
//1 = eye
//2 = pupil
//0 = off


void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);


Serial.begin(9600);


}

void loop() {
//Serial.println(" ");
//Serial.println("starts");
Translate(base);
//Serial.println("translates");

//Serial.println("writes");
  FastLED.show();
  delay(2000);


//Serial.println("shows");




}



  void Translate(CRGB untrans[ROWS][COLLUMS])
{





      int rowStart;
      int rowEnd;
      int rowChange;


  int index = 0;
  bool reverse = false;
  //Serial.println("trans: sets values");
  for(int c = COLLUMS - 1 ; c >= 0; c-- ) {
    if(!reverse) {
       rowStart = 0;
       rowEnd = ROWS - 1;
       rowChange = 1;
       //Serial.println("trans: not reversed");
       
    } else {
       rowStart = ROWS;
       rowEnd = -1;
       rowChange = -1;
       //Serial.println("trans: reverses");
    }
    //Serial.println(rowStart);
    //Serial.println(rowEnd);
    //Serial.println(rowChange);
    //Serial.println(" ");


  for(int r = rowStart ; r != rowEnd; r = r + rowChange ) {
      Serial.println(r);

      leds[index] = untrans[r][c];
      index++;

      
    


  }
  //Serial.println("trans: indexes");
  reverse = !reverse;
  //Serial.println("trans: " + reverse);
}


}

