/*PHTOTOSYNTHESIS, Task 4 : Open the flower if it is the day, and close the flower if it is the night . */

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
// Touch sensor
CAP1203 touch_sensor=CAP1203(ADD_TOUCH); 
//Light sensor 
RPR0521RS rpr0521rs;
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

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
 Serial.println("Photosynthesis : Task 4 ");

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);

 //Touch sensor initialisation
 touch_sensor.begin();
 
 // Light sensor initialisation
 luminosity_sensor = rpr0521rs.init();

  //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();


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

    //Day
    //The flower is opening 
    if ((luminosity >= luminosity_limit)&& (current_position< FLOWER_CLOSE_TO_OPEN))
    { 
      stepper.rotate(360); 
      current_position=current_position +1;
    }
    //Night
    //The flower is closing 
     else if ((luminosity < luminosity_limit) &&(current_position>0 ))
     {
       stepper.rotate(-360); 
       current_position=current_position -1;
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