/*BEE,Task 3 : Change the color of the bionic flower */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>

/*GPIO*/
//Vibrating motor pin
#define MOTOR_PIN 22
//Hall sensor pin
#define HALL_PIN 21
//LED pin
#define LED_PIN 16

/*Variable*/
//If a magnet is detected; Magnet = 0. Otherwise Magnet = 1
int magnet;
//Number of the LEDs
#define NUM_LEDS 5

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];

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

/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Bee scenario : Task 3");
 
 //Define the vibrating motor as a output
 pinMode(MOTOR_PIN, OUTPUT);
 //Turn off the vibrating motor
 digitalWrite(MOTOR_PIN, LOW);

 //Define the hall sensor as a imput
 pinMode(HALL_PIN,INPUT);

 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();
}

/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
   //Change the color of the bionic flower
    color_day();
    delay(1000);
    color_night();
    delay(1000);
    
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
