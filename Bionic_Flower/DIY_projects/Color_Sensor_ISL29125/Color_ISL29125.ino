/* Color sensor's exemple. */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// color sensor's library
#include "SparkFunISL29125.h"

/*GPIO*/
//LED pin
#define LED_PIN 16
//I2C communication pin 
#define I2C_SDA 4
#define I2C_SCL 5

/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
//Address of the color sensor
#define ADD_COLOR 0x44
// R G B value for the white color
unsigned int redhigh , greenhigh, bluehigh;
// R G B value for the black color
unsigned int redlow, greenlow, bluelow;
// R G B value for the color which has been detected 
unsigned int R,G,B;

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
// Color sensor
SFE_ISL29125 RGB_sensor;

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

//The calibration_color() function allows to calibrate the high (white) and the low (black) value 
void BW_calibration()
{  
   // Color sensor selected, start the transmission
   Wire.beginTransmission(ADD_COLOR);

   //White color calibration
   Serial.println("Please, place the sensor on white color ...");
   delay(3000);
   redhigh = RGB_sensor.readRed();
   greenhigh = RGB_sensor.readGreen();
   bluehigh = RGB_sensor.readBlue();
   delay(3000);
   
   //Black color calibration
   Serial.println("Please, place the sensor on black color ...");
   delay(3000);
   redlow = RGB_sensor.readRed();
   greenlow = RGB_sensor.readGreen();
   bluelow = RGB_sensor.readBlue();
   delay(3000);

    // The end of the transmission
    Wire.endTransmission();
}


//link RGB code : https://www.w3schools.com/colors/colors_picker.asp
//The color_sensor() function allows to read the RGB value of the color 
void Read_RGB()
{ 
  // Color sensor selected 
  Wire.beginTransmission(ADD_COLOR);
  
  //Color sensor parameters
  unsigned int red_value, green_value ,blue_value;

  // Read sensor values (16 bit integers)
  red_value = RGB_sensor.readRed();
  green_value = RGB_sensor.readGreen();
  blue_value = RGB_sensor.readBlue();  
  // Convert to RGB values 
  red_value = map(red_value, redlow, redhigh, 0, 255);
  green_value = map(green_value, greenlow, greenhigh, 0, 255);
  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
  // Constrain to values of 0-255
  R = constrain(red_value, 0, 255);
  G = constrain(green_value, 0, 255);
  B = constrain(blue_value, 0, 255);

  // Display the RGB value on the serial monitor
  Serial.print("COLOR : "); Serial.print("R "); Serial.print(R); Serial.print("G "); Serial.print(G); Serial.print("B ");Serial.println(B);   

 
  // The end of the transmission
  Wire.endTransmission();
   
}


/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
  //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Color sensor ");
 
 ///LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 //Color sensor initialisation
 RGB_sensor.init();
 //Black and White calibration 
 BW_calibration();
      
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  

  // Read the RGB value from the color which has been detected 
  Read_RGB();

  // Turn on the LEDs with the RGB value from the color sensor
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(R,G,B);
  }
  FastLED.show();

  //Wait 500 ms
  delay(500);
  
}
