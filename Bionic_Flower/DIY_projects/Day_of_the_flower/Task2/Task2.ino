/*DAY OF THE FLOWER, Task 2  : Implement the light sensor and 
change the color depending on the luminosity value . */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// light sensor's library
#include "RPR-0521RS.h"

/*GPIO*/
//LED pin
#define LED_PIN 16
//I2C communication pin 
#define I2C_SDA 4
#define I2C_SCL 5

/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
//I2C adress light sensor 
#define ADRESS_LIGHT 0x38
//Luminosity sensor
uint8_t luminosity_sensor;
//Proximity value
uint32_t proximity;
//Luminosity value
float luminosity;
// Limit between the night and the morning (depend on the ambiant luminosity)
float lum_night_morning = 400;
//Limit between the morning and the day (depend on the ambiant luminosity)
float lum_morning_day = 800;

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
//Light sensor 
RPR0521RS rpr0521rs;

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
 Serial.println("Day of the flower : Task 2");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();
 
 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);

 // Light sensor initialisation
 luminosity_sensor = rpr0521rs.init();


}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{
  
  //Read the luminosity value
 Wire.beginTransmission(ADRESS_LIGHT);
 luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
 Serial.print("Luminosity =");
 Serial.println(luminosity);
 Wire.endTransmission();

 //Night
 if ( luminosity < lum_night_morning) 
 {
  color_night();
 }
 //Day
 else if (luminosity > lum_morning_day)
 {
  color_day();
 }
 //Morning
 else 
 {
  color_morning();
 }


  
}
