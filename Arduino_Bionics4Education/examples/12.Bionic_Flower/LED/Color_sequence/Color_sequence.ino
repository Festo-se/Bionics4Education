/* Hi ! This example will teach you how to use the bionic flower LEDs. There are 5 LEDs. To control a led you have to give it an RGB code.*/

// LED's library 
#include<FastLED.h>

// LED GPIO
#define LED_PIN 16
#define NUM_LEDS 5 

//OBJECT CREATION : LED
CRGB leds[NUM_LEDS];

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

// The red_color() function allows to light LEDs in red
void red_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255,0,0);
  }
  FastLED.show();
}
// The green_color() function allows to light LEDs in green
void green_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0,255,0);
  }
  FastLED.show();
}
// The blue_color() function allows to light LEDs in blue
void blue_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0,0,255);
  }
  FastLED.show();
}


void setup() {
     //start the serial communication 
     Serial.begin(9600);
     // initialise LEDs
     FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
}

void loop() {
  
    //Color sequence 
    red_color();
    delay(500);
    green_color();
    delay(500);
    blue_color();
    delay(500);

}
