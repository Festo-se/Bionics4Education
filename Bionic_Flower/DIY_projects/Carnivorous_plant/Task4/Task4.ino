/*Carnivorous plant,Task 4: The flower is closing and the LED red  are flashing if the forward movement is detected
and the flower is opening if the backward movement is detected  */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// motor's library
#include "BasicStepperDriver.h"
// gesture sensor's library
#include "paj7620.h"


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
//Motor number's steps (1.8deg)
#define MOTOR_STEPS 200
//Revolutions per second
int RPM = 240;
//Full step mode selected
#define MICROSTEPS 1
//Number of turns to go from closed to open state
#define FLOWER_CLOSE_TO_OPEN 120
// I2C address gesture snesor 
#define ADD_GEST 0x43
//Position of the motor between full open (120) and full close(0)
int current_position; 
// Gesture sensor value for the right movement
int right =1;
// Gesture sensor value for the left movement
int left= 2;
// Gesture sensor value for the up movement
int up = 4;
// Gesture sensor value for the down movement
int down = 8;
// Gesture sensor value for the forward movement
int forward = 16;
// Gesture sensor value for the backward movement
int backward = 32;
// Gesture sensor value for the clockwise movement
int clockwise = 64;
// Gesture sensor value for the anti-clockwise movement
int anti_clockwise = 128;

 
/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
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
 Serial.println("Carnivorous plant : Task 4");

  //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 //the flower is opening (initial position)
 while(current_position < FLOWER_CLOSE_TO_OPEN)
  { 
    stepper.rotate(360);
    current_position = current_position +1;
  }

 //Gesture sensor initialisation
 uint8_t error = paj7620Init();  

 //initial color 
  green_color();
 
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  
  //Read the gesture sensor value
  byte gesture;
  int error;
  error = paj7620ReadReg(ADD_GEST, 1, &gesture);
  Serial.print("Gesture :  ");
  Serial.println(gesture);

  //the flower is closing and the LEDs is red and light
  if (gesture == forward)
  {
    Serial.println("Forward"); 
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
       delay(3000);//3s
       red_LED=false;
     
  }
  //the flower is opening 
  else if (gesture == backward)
  { 
    if (current_position != FLOWER_CLOSE_TO_OPEN)
    {
    Serial.println("Backward");
    green_color(); 
    //Low speed
     RPM=100;
     stepper.begin(RPM, MICROSTEPS);
    //the flower is opening 
    while (current_position < FLOWER_CLOSE_TO_OPEN)
     {  stepper.rotate(360); 
          current_position=current_position +1;}
    }
  }
 
}
