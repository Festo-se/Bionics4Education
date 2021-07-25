/*DAY OF THE FLOWER,Task 1 : Change the LED's color .  */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>

/*GPIO*/
//LED pin
#define LED_PIN 16

/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];


/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

//The color_morning() function allows to light the flower in orange
void color_morning()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,60,21);
  }
  FastLED.show();
}
//The color_day() function alloows to light the flower in yellow
void color_day()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,127,0);;
  }
  FastLED.show();
}

//The color_night() function allows to light the flower in blue
void color_night()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(96,80,220);
  }
  FastLED.show();
}
//The black_color() function allows to turn off the bionic flower
void black_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}


/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Day of the flower : Task 1");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{

  color_night();
  delay(500);
  color_morning();
  delay(500);
  color_day();
  delay(500);
  
}
