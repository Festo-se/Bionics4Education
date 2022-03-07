/* Hi ! This example will teach you how to use the bionic flower light sensor. The sensor measures the luminosity vaue.
 If the luminosity is superior than the limit defined by the Luminosity_limit variable, the flower lights yellow. Otherwise, the color is blue.
The sensor use the I2C communication.*/

// Light sensor's library
#include "RPR-0521RS.h"
//I2C communication library 
#include <Wire.h>
// LED's library 
#include<FastLED.h>

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 

// LED GPIO
#define LED_PIN 16
#define NUM_LEDS 5 

//object creation : LED
CRGB leds[NUM_LEDS];
// object creation : light sensor 
RPR0521RS rpr0521rs;
int rc;

int Luminosity_limit = 200;//this value depends on the ambiant luminosity 


//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

// The red_color() function allows to light LEDs in red
void yellow_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255,255,0);
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
     //start the I2C communication 
     Wire.begin(I2C_SDA, I2C_SCL, 100000);
     //Initialisation light sensor 
     rc = rpr0521rs.init();
     // initialise LEDs
     FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
}

void loop() {

  uint32_t proximity;
  float luminosity;
  rc = rpr0521rs.get_psalsval(&proximity,&luminosity);
  Serial.print("Luminosity : "); Serial.print(luminosity);Serial.println(" [lx] ");
  if (luminosity > Luminosity_limit)
  {
    yellow_color();
  }
  else {
    blue_color();
  }
  delay(500);

}
