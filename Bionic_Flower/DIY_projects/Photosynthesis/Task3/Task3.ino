/*PHTOTOSYNTHESIS, Task 3 : Using the luminsoity sensor . */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
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
// Number of colors ( red, blue, green, yellow)
int num_color = 4;
// Value of the random color for the beginning ( Red =0, Blue = 1, Green =2, Yellow= 3)
int color;
// Address touch sensor
#define ADD_TOUCH 0x28
//I2C adress light sensor 
#define ADD_LIGHT 0x38
//Luminosity sensor
uint8_t luminosity_sensor;
//Proximity value
uint32_t proximity;
//Luminosity value
float luminosity;
// Limit between day and night (depend on the ambiant luminosity)
float luminosity_limit = 400;


/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
// Touch sensor
CAP1203 touch_sensor=CAP1203(ADD_TOUCH); 
//Light sensor 
RPR0521RS rpr0521rs;

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
 Serial.println("Photosynthesis : Task 3");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);

 //Touch sensor initialisation
 touch_sensor.begin();

 // Light sensor initialisation
 luminosity_sensor = rpr0521rs.init();

// Selection of a random a color
  color = random(num_color);
  // The flower lights in the start color 
  if (color == 0)
  { 
    red_color();
  }
  else if (color == 1) 
  { 
    green_color();
  }
  else if (color == 2) 
  {
    blue_color();
  }
  else if (color==3)
  { 
    yellow_color();
  }

  
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{ 
  
    //Start the transmission with the light sensor 
    Wire.beginTransmission(ADD_LIGHT);
    //Read the luminsity value
    luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
    Serial.println("Luminosity value");
    Serial.println(luminosity);
    // End the transmission with the light sensor
    Wire.endTransmission();

    if (luminostity > luminosity_limit)
    {
      Serial.println("Day");
    }
    else 
    {
      Serial.println("Night");
    }
//
//    // Start the transmission with the touch sensor
//  Wire.beginTransmission(ADD_TOUCH);
//
////No touch detected 
//  while ((touch_sensor.isLeftTouched() == false)&&(touch_sensor.isRightTouched() == false))
//  { 
//    Serial.println("No touch detected");
//    
//  }
//
////End the transmission with the touch sensor
//    Wire.endTransmission();
//   
//   //Touch detected 
//   color= color+1;     
//   // Change the flower's color
//   if (color == 1) 
//   { 
//    red_color();
//   }
//   else if (color == 2)
//   {
//    green_color();
//   }
//   else if (color == 3)
//   {
//    blue_color();
//   }
//   else if (color == 4)
//   { 
//    yellow_color();
//    color=0;
//   }
//
//   delay(2000);
//  
}
