/*Carnivorous plant,Task 2 : if a touch is detected the flower flashing in red. Otherwise the flower is green */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>


/*GPIO*/
//LED pin
#define LED_PIN 16
//I2C communication pin 
#define I2C_SDA 4
#define I2C_SCL 5

/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
// If LED is light up in red, red_LED = true. Otherwise red_LED = false  
boolean red_LED = false;
// I2C address touche snesor 
#define ADD_TOUCH 0x28
 
/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
// Touch sensor
CAP1203 touch_sensor=CAP1203(ADD_TOUCH); 

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
//The green_color() function allows to light the flower in green
void green_color()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(51,204,51);
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
 Serial.println("Carnivorous plant : Task 2");
 
 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 
 //Touch sensor initialisation
 touch_sensor.begin();

 //Turn on the LEDs in the green color
 green_color();


}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
   // No touch detected
    while((touch_sensor.isLeftTouched() == false) &&(touch_sensor.isRightTouched() == false))
    {
      green_color();
    }

    //Touch detected
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

      
}
