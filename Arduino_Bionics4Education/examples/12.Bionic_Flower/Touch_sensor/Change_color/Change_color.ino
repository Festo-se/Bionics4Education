/* Hi ! This example will teach you how to use the bionic flower touch sensor.The sensor detects when you touch right or left.
If a right touch is detected the color change for the next color. If a left touch is detected the color change for the previous color.
The sensor use the I2C communication.*/

// Touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
//I2C communication library 
#include <Wire.h>
// LED's library 
#include<FastLED.h>

// LED GPIO
#define LED_PIN 16
#define NUM_LEDS 5 

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 

//object creation : LEDs
CRGB leds[NUM_LEDS];
//Object creation : touch sensor 
CAP1203 touch_sensor=CAP1203(0x28); 

boolean Red=false;
boolean Green= false;
boolean Blue= false;

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

// The red_color() function allows to light LEDs in red
void red_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255,0,0);
  }
  FastLED.show();
}
// The green_color() function allows to light LEDs in green
void green_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0,255,0);
  }
  FastLED.show();
}
// The blue_color() function allows to light LEDs in blue
void blue_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0,0,255);
  }
  FastLED.show();
}


void setup() {
  
     //start the serial communication 
     Serial.begin(9600);
     //start the I2C communication 
     Wire.begin(I2C_SDA, I2C_SCL, 100000);
     // initialise LEDs
     FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS); 
     
     delay(5000); //time to open the serial monitor
     // Touch sensor is connected ? 
     while (touch_sensor.begin() == false) 
     {
      Serial.println("Not connected. Please check connections.");
      delay(1000);
      }
     Serial.println("Touch sensor connected!");

     blue_color();
     Blue = true;
}

void loop() {
    // Change the color for the next color
    if (touch_sensor.isRightTouched() == true)
    {
      Serial.println("Right");
      if ( Red == true) 
      {
        green_color();
        Green=true;
        Red=false;
      }
      else if ( Green == true) 
      {
        blue_color();
        Blue=true;
        Green=false;
      }
      else if ( Blue == true) 
      {
        red_color();
        Red=true;
        Blue=false;
      }  
   }
   //Change the color for the previous color
    if (touch_sensor.isLeftTouched() == true)
    {
      Serial.println("Left");
      if ( Red == true) 
      {
        blue_color();
        Blue=true;
        Red=false;
      }
      else if ( Green == true) 
      {
        red_color();
        Red=true;
        Green=false;
      }
      else if ( Blue == true) 
      {
        green_color();
        Green=true;
        Blue=false;
      }  
    }
    
    delay(500);
}
