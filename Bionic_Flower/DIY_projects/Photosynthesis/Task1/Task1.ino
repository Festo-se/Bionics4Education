/*PHTOTOSYNTHESIS, Task 1 : Change the LED's color . */

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
/*Variable*/
// Number of colors ( red, blue, green, yellow)
int num_color = 4;
// Value of the flower's color ( Red =0, Blue = 1, Green =2, Yellow= 3)
int color;

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

//The blue_color() function allows to light the bionic flower in blue
void blue_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,255);
  }
  FastLED.show();
}

//The green_color() function allows to light the bionic flower in green
void green_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,255,0);//Vert
  }
  FastLED.show();
}

//The red_color() function allows to light the bionic flower in red
void red_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,0,0);
  }
  FastLED.show();
}

//The yellow_color() function allows to light the bionic flower in yellow
void yellow_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(223,109,20);
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
 Serial.println("Photosynthesis : Task 1");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 color = 0;
 
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{
  
    color= color+1;     
   // Change the flower's color
   if (color == 1) 
   { 
    red_color();
   }
   else if (color == 2)
   {
    green_color();
   }
   else if (color == 3)
   {
    blue_color();
   }
   else if (color == 4)
   { 
    yellow_color();
    color=0;
   }

   delay(2000);

}
