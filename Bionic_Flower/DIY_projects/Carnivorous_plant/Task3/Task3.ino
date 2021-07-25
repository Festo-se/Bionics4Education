/*Carnivorous plant,Task 3 : The flower is closing and LED flash red if a touch is detected */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
// motor's library
#include "BasicStepperDriver.h"


/*GPIO*/
//LED pin
#define LED_PIN 16
//I2C communication pin 
#define I2C_SDA 4
#define I2C_SCL 5
//Motor pin 
#define DIR 33
#define STEP 25
#define SLEEP 13


/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
// If LED is light up in red, red_LED = true. Otherwise red_LED = false  
boolean red_LED = false;
// I2C address touche snesor 
#define ADD_TOUCH 0x28
//Motor number's steps (1.8deg)
#define MOTOR_STEPS 200
//Revolutions per second
int RPM = 240;
//Full step mode selected
#define MICROSTEPS 1
//Number of turns to go from closed to open state
#define FLOWER_CLOSE_TO_OPEN 120
//Position of the motor between full open (120) and full close(0)
int current_position; 

 
/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
// Touch sensor
CAP1203 touch_sensor=CAP1203(ADD_TOUCH); 
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

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
//The motor_calibration() function allows the flower to be completely closed (initial position)
void motor_calibration()
{
    for (int i =0; i<FLOWER_CLOSE_TO_OPEN;i++)
    { stepper.rotate(-360);}
    
    current_position=0;
    Serial.println("Calibatrion motor done");    
}


/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Carnivorous plant : Task 3");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 
 //Touch sensor initialisation
 touch_sensor.begin();
 
 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 //the flower is opening (initial position)
 while(current_position < FLOWER_CLOSE_TO_OPEN)
  { 
    stepper.rotate(360);
    current_position = current_position +1;
  }

  //Turn on the LEDs in the green (initial color)
  green_color();
 
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  
  //if no touch is detected, the flower is opening slowly and lights in green color 
   //Low speed
   RPM=100;
   stepper.begin(RPM, MICROSTEPS);
   while((touch_sensor.isLeftTouched() == false) &&(touch_sensor.isRightTouched() == false))
   {   // the flower is opening 
       if (current_position < FLOWER_CLOSE_TO_OPEN)
        { stepper.rotate(360);
          current_position=current_position +1;
        }
   } 

  //Touch sensor is detected ->  flower is closing speedly and flashing 
   //Fast speed
   RPM=450;
   stepper.begin(RPM, MICROSTEPS); 
   //the flower is closing   
   while (current_position >0)
   {  stepper.rotate(-360); 
      current_position=current_position -1; 
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
     red_color();
     //Wait 3s
     delay(3000);
     //Initial color
     green_color();
     red_LED=false;
  
}
