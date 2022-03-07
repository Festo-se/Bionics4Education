/* Hi ! This example will teach you how to use the bionic flower touch sensor and the light sensor.
If a right touch is detected the flower is opening. If a left touch is detected the flower is closing.
In addition, if the luminosity is enough the flower is yellow, otherwise the flower is yellow.
The sensor use the I2C communication.*/

// Touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
//I2C communication library 
#include <Wire.h>
//motor's library 
#include "BasicStepperDriver.h"
// Light sensor's library
#include "RPR-0521RS.h"
// LED's library 
#include<FastLED.h>

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 
//I2C Adress
#define ADD_Touch 0x28
#define ADD_Light 0x38

//motor GPIO
#define DIR 33
#define STEP 25
#define SLEEP 13
//MOTOR CHARACTERISTIC 
//1.8 degree/step
#define MOTOR_STEPS 200 
#define MICROSTEPS 1

// LED GPIO
#define LED_PIN 16
#define NUM_LEDS 5 

//Object creation : touch sensor 
CAP1203 touch_sensor=CAP1203(0x28); 
//Object creation : motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
//object creation : LED
CRGB leds[NUM_LEDS];
// object creation : light sensor 
RPR0521RS rpr0521rs;
int rc;

//speed
int RPM=240; 
//number of turns to go from state: full close to full open
int FLOWER_CLOSE_TO_OPEN = 120;
//position of the motor between full open and full close 
int current_position; 

int Luminosity_limit = 200;//this value depends on the ambiant luminosity 

//link RGB code : https://www.w3schools.com/colors/colors_picker.asp

// The red_color() function allows to light LEDs in red
void yellow_color()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255,255,0);
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


//The motor_calibration() function allows completely close the flower. It's the initial position of the flower.
void motor_calibration()
{
    for (int i =0; i<FLOWER_CLOSE_TO_OPEN;i++)
    { stepper.rotate(-360);}
    current_position=0;
    Serial.println("Calibatrion motor done");
    
}

void setup() {
  
     //start the serial communication 
     Serial.begin(9600);
     //start the I2C communication 
     Wire.begin(I2C_SDA, I2C_SCL, 100000);
     
     delay(5000); //time to open the serial monitor
     // Touch sensor is connected ? 
     while (touch_sensor.begin() == false) 
     {
      Serial.println("Not connected. Please check connections.");
      delay(1000);
      }
     Serial.println("Touch sensor connected!");
     
    //initialise the motor
     stepper.begin(RPM, MICROSTEPS);
     motor_calibration();
     //Initialisation light sensor 
     rc = rpr0521rs.init();
     // initialise LEDs
     FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
}

void loop() {

    Wire.beginTransmission(ADD_Light);
    uint32_t proximity;
    float luminosity;
    rc = rpr0521rs.get_psalsval(&proximity,&luminosity);
    Serial.print("Luminosity : "); Serial.print(luminosity);Serial.println(" [lx] ");
    Wire.endTransmission();

    while(luminosity > Luminosity_limit)
    {
      yellow_color();
      Wire.beginTransmission(ADD_Touch);
      //the flower is opening 
      if (touch_sensor.isRightTouched() == true)
      {
        Serial.println("Right");
        if (current_position < FLOWER_CLOSE_TO_OPEN)
        { 
          stepper.rotate(360);
          current_position = current_position +1;
        }
        
     }
     //the fower is closing 
      else if (touch_sensor.isLeftTouched() == true)
      {
       Serial.println("Left");
       if (current_position > 0) 
       {
        stepper.rotate(-360);
        current_position = current_position -1;
       }
      }
      Wire.endTransmission();

     Wire.beginTransmission(ADD_Light);
     rc = rpr0521rs.get_psalsval(&proximity,&luminosity);
    Serial.print("Luminosity : "); Serial.print(luminosity);Serial.println(" [lx] ");
    Wire.endTransmission();
      
    }
  
    blue_color();
}
