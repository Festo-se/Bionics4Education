/*Carnivorous plant,Task 5: The flower is closing and the LED red  are flashing if the forward movement is detected
and the flower is opening if the backward movement is detected. 
In addition, you can change the color with "right" and "left" movement 
and the intensity of the color with "down" and "up" movement.
You can create a load movement with the "clockwise" or "anti-clockwise" movement. 
*/
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
// Number of the color (blue, red, green, pink, yellow)
int nb_color = 5;
//Number of intensity for each color
int nb_intensity = 3;
// Variable allows to know what is the current color  
int current_color;
// Variable allows to know what is the current intensity level
int current_intensity;

 
/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

//The blue_1() function lights the flower in blue with a little itensity
void blue_1()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(116,208,241);
  }
  FastLED.show();
}
//The blue_2() function lights the flower in blue with a medium itensity
void blue_2()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(58,142,186);
  }
  FastLED.show();
}
//The blue_3() function lights the flower in blue with a high itensity
void blue_3()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(15,5,107);
  }
  FastLED.show();
}
//The green_1() function lights the flower in green with a little itensity
void green_1()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(130,196,108);
  }
  FastLED.show();
}
//The green_2() function lights the flower in green with a medium itensity
void green_2()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,86,27);
  }
  FastLED.show();
}
//The green_3() function lights the flower in green with a high itensity
void green_3()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,255,0);
  }
  FastLED.show();
}
//The red_1() function lights the flower in red with a little itensity
void red_1()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(204,78,92);
  }
  FastLED.show();
}
//The red_2() function lights the flower in red with a medium itensity
void red_2()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(238,16,16);
  }
  FastLED.show();
}
//The red_3() function lights the flower in red with a high itensity
void red_3()
{ 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,0,0);
  }
  FastLED.show();
}
//The yellow_1() function lights the flower in yellow with a little itensity
void yellow_1()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(254,248,108);
  }
  FastLED.show();
}
//The yellow_2() function lights the flower in yellow with a medium itensity
void yellow_2()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(252,210,28);
  }
  FastLED.show();
}
//The yellow_3() function lights the flower in yellow with a high itensity
void yellow_3()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,255,0);
  }
  FastLED.show();
}
//The pink_1() function lights the flower in pink with a little itensity
void pink_1()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(254,191,210);
  }
  FastLED.show();
}
//The pink_2() function lights the flower in pink with a medium itensity
void pink_2()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(243,63,146);
  }
  FastLED.show();
}
//The pink_3() function lights the flower in pink with a high itensity
void pink_3()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(128,0,128);
  }
  FastLED.show();
}
//The black_color() allows to turn off the bionic flower
void black_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}
//The color() function allows to lights the bionic flower in the color as the color variable and with the intensity as the intensity value
void color(int color,int intensity)
{ 
 
  if ( color == 0)//Blue color 
  {
    if ( intensity == 0)
    {
      blue_1();
    }
    else if (intensity == 1)
    {
      blue_2();
    }
    else if (intensity == 2)
    {
      blue_3();
    }
  }
  else if (color == 1)//Green color
  {
    if ( intensity == 0)
    {
      green_1();
    }
    else if (intensity == 1)
    {
      green_2();
    }
    else if (intensity == 2)
    {
      green_3();
    }
  }
  else if (color == 2)//Red color
  {
    if ( intensity == 0)
    {
      red_1();
    }
    else if (intensity == 1)
    {
      red_2();
    }
    else if (intensity == 2)
    {
      red_3();
    }
  }
  else if (color == 3)//Yellow color
  {
    if ( intensity == 0)
    {
      yellow_1();
    }
    else if (intensity == 1)
    {
      yellow_2();
    }
    else if (intensity == 2)
    {
      yellow_3();
    }
  }
  else if (color == 4)//Pink color
  {
    if ( intensity == 0)
    {
      pink_1();
    }
    else if (intensity == 1)
    {
      pink_2();
    }
    else if (intensity == 2)
    {
      pink_3();
    }
  }
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
 Serial.println("Carnivorous plant : Task 5");

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);

 //Gesture sensor initialisation
 uint8_t error = paj7620Init();  
 
 //LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 //the flower is opening (initial position)
 while(current_position < FLOWER_CLOSE_TO_OPEN)
  { 
    stepper.rotate(360);
    current_position = current_position +1;
  }

 //initial color 
 color(random(nb_color),random(nb_intensity));
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  
  //Read the gesture sensor value
  byte gesture;
  int error;
  error = paj7620ReadReg(0x43, 1, &gesture);
  Serial.print("Gesture :  ");
  Serial.println(gesture);

  //next color
  if (gesture == right)
  {
    Serial.println("Right"); 
    current_color= current_color+1;
    if (current_color == nb_color){current_color =0;}

    color(current_color, current_intensity);
  }
  //previous color 
  else if (gesture == left)
  {
    Serial.println("Left"); 
    current_color = current_color -1;
    if (current_color == -1) { current_color = nb_color-1;}
    
    color(current_color, current_intensity);
  }
  // Increase the intensity
  else if (gesture == up)
  {
    Serial.println("Up");
    if ( current_intensity < nb_intensity-1)//<=1
    {
    current_intensity=current_intensity+1;
    }
    color(current_color, current_intensity);
     
  }
  //Desecrease the intensity
  else if (gesture == down)
  {
    Serial.println("Down"); 
    if ( current_intensity >0)
    {
    current_intensity=current_intensity-1;
    }
    color(current_color, current_intensity);
  }


  
  //Load movement in anticlockwise
  else if (gesture == anti_clockwise)
  {
    Serial.println("Anti clockwise");
    
    black_color();
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(96,80,220);
    FastLED.show();
    delay(500);
    leds[i]=CRGB(0,0,0);
    FastLED.show();
    
    }
    color(current_color, current_intensity);
     
  }
  //Load movement in clockwise
  else if (gesture == clockwise)
  { 
    Serial.println("Clockwise");
    black_color(); 
     for (int i = NUM_LEDS-1; i >= 0;i=i-1) {
    leds[i] = CRGB(96,80,220);
    FastLED.show();
    delay(500);
    leds[i]=CRGB(0,0,0);
    FastLED.show();
    
    }
    color(current_color, current_intensity);
    
  }
  //the flower is closing and the LEDs is red and light
  else if (gesture == forward)
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
          red_2();
          red_LED=true;
        }
        else 
        { 
          black_color();
          red_LED=false;
        }
     
     }
       red_2();
       delay(3000);//3s
       red_LED=false;
     
  }
  //the flower is opening 
  else if (gesture == backward)
  { 
    if (current_position != FLOWER_CLOSE_TO_OPEN)
    {
    Serial.println("Backward");
    color(random(nb_color),random(nb_intensity));
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
