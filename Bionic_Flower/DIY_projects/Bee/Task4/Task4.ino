/*BEE,Task 4: Open and close the bionic flower */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// motor's library
#include "BasicStepperDriver.h"

/*GPIO*/
//Vibrating motor pin
#define MOTOR_PIN 22
//Hall sensor pin
#define HALL_PIN 21
//LED pin
#define LED_PIN 16
//Motor pin 
#define DIR 33
#define STEP 25
#define SLEEP 13

/*Variable*/
//If a magnet is detected; Magnet = 0. Otherwise Magnet = 1
int magnet;
//Number of the LEDs
#define NUM_LEDS 5
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

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

//The color_day() function alloows to light the flower in yellow
void color_day()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,127,0);
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
 Serial.println("Bee scenario : Task 4");
 
 //Define the vibrating motor as a output
 pinMode(MOTOR_PIN, OUTPUT);
 //Turn off the vibrating motor
 digitalWrite(MOTOR_PIN, LOW);

 //Define the hall sensor as a imput
 pinMode(HALL_PIN,INPUT);

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();
}

/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
      
    color_day();
   //the motor is opening
    while(current_position< FLOWER_CLOSE_TO_OPEN)
    {stepper.rotate(360);  
    current_position=current_position +1;}

    delay(1000);
    
    color_night();
    // the motor is closing
   while(current_position>0)
   {stepper.rotate(-360); 
    current_position=current_position -1;}
  
    
//    //Read the hall sensor
//    magnet = digitalRead( HALL_PIN);
//    Serial.println("Magnet");
//    Serial.println(magnet);
//
//    //a magnet is detected
//    if (magnet == 0)
//    {//Turn on the vibrating motor 
//      digitalWrite(MOTOR_PIN,HIGH);
//    }
//    //a magnet isn't detected 
//    else 
//    { //Turn off the vibrating motor
//      digitalWrite(MOTOR_PIN, LOW);
//    }
}
