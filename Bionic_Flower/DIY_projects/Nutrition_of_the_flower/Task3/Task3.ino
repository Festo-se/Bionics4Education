/*Nutrition of the flower , Task 3 : Create the load movement for the LEDs  */

/*Library*/
#include <Arduino.h>
// motor's library
#include "BasicStepperDriver.h"
// I2C communication library
#include <Wire.h>
// light sensor's library
#include "RPR-0521RS.h"
// LED's library
#include<FastLED.h>


/*GPIO*/
//Motor pin 
#define DIR 33
#define STEP 25
#define SLEEP 13
//I2C communication pin 
#define I2C_SDA 21
#define I2C_SCL 22
//LED pin
#define LED_PIN 16

/*Variable*/
//Motor number's steps (1.8deg)
#define MOTOR_STEPS 200
//Revolutions per second
#define RPM 240
//Full step mode selected
#define MICROSTEPS 1
//Number of turns to go from closed to open state
#define FLOWER_CLOSE_TO_OPEN 120
//Position of the motor between full open (120) and full close(0)
int current_position; 
//Luminosity sensor
uint8_t luminosity_sensor;
//Proximity value
uint32_t proximity;
//Luminosity value
float luminosity;
// Limit between day and night (depend on the ambiant luminosity)
float luminosity_limit = 400;
//Number of the LEDs
#define NUM_LEDS 5

/*Obejct*/
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
//Light sensor 
RPR0521RS rpr0521rs;
//LED
CRGB leds[NUM_LEDS];

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/
//The motor_calibration() function allows the flower to be completely closed (initial position)
void motor_calibration()
{
    for (int i =0; i<FLOWER_CLOSE_TO_OPEN;i++)
    { stepper.rotate(-360);}
    
    current_position=0;
    Serial.println("Calibatrion motor done");    
}

//The blue_color() function allows to light the bionic flower in blue
 void blue_color()
{
   for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,255);
  }
  FastLED.show();

}

//The black_color() function allows to turn off the flower's LEDs
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
 Serial.println("Nutrition of the flower scenario : Task 3");

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 // Light sensor initialisation
 luminosity_sensor = rpr0521rs.init();

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
   //Load movement
  for (int i = 0; i < NUM_LEDS; i++) {
      //Blue
      leds[i] = CRGB(96,80,220);
      FastLED.show();
      delay(1000);
      //Black
      leds[i]=CRGB(0,0,0);
      FastLED.show();            
  }

    
//  //Read the luminosity value
// luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
// Serial.println("Luminosity value");
// Serial.println(luminosity);
//
// //Day
// while (luminosity >= luminosity_limit)
// {
//   //the flower is opening 
//   if(current_position < FLOWER_CLOSE_TO_OPEN)
//    { 
//      stepper.rotate(360);
//      current_position = current_position +1;
//    }
//    //Read the luminosity value
//     luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
//     Serial.println("Luminosity value");
//     Serial.println(luminosity);
// } 
//   //No the day = Night 
//   //the fower is closing 
//   if(current_position > 0) 
//   {
//    stepper.rotate(-360);
//    current_position = current_position -1;
//   }

}
