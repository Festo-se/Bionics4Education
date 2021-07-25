/*Carnivorous plant,Task 1 : Flashing the bionic flower  */

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
// If LED is light up in red, red_LED = true. Otherwise red_LED = false  
boolean red_LED = false;
 
/*Obejct*/
//LED
CRGB leds[NUM_LEDS];

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

//The red_color() function alloows to light the flower in red
void red_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,42,1);
  }
  FastLED.show();
}

//The green() function allows to light up the flower in green 
void green_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,255,0);
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
 Serial.println("Carnivorous plant : Task 1");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //Turn on the LED in green color
 green_color();
 //Wait 2s 
 delay(2000);

}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
    //flashing    
    if (red_LED == false )
    { 
      red_color();
      red_LED=true;
    }
    else 
    { 
      black_color();
      red_LED=false;
    }
    //Wait 2s
    delay(2000);
    
    
  
}
