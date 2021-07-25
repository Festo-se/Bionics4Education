/*Diversity of the flower , Task 5 : A first color is detected, the flower lights like this color and open (50%).
Then a second color is detected, and if a breath is detected with the CO2 sensor, the flower fully open (100%)
and lights in the mixing color. */

/*Library*/
#include <Arduino.h>
// LED's library
#include<FastLED.h>
// I2C communication library
#include <Wire.h>
// color sensor's library
#include "SparkFunISL29125.h"
// motor's library
#include "BasicStepperDriver.h"
// CO2 sensor's library
#include "Adafruit_SGP30.h"

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
//Address of the color sensor
#define ADD_COLOR 0x44
// R G B value for the white color
unsigned int redhigh , greenhigh, bluehigh;
// R G B value for the black color
unsigned int redlow, greenlow, bluelow;
// R G B value for the red color
int Red_R, Red_G, Red_B;
// R G B value for the green color
int Green_R, Green_G, Green_B;
// R G B value for the blue color
int Blue_R, Blue_G, Blue_B;
// RED = true if the red color is detected, otherwise false
boolean RED = false ;
// GREEN = true if the green color is detected, otherwise false
boolean GREEN = false;
// BLUE = true if the blue color is detected, otherwise false
boolean BLUE = false;
//Range (a margin of error for the RGB value) 
int range = 10;
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
// Address of the C02 sensor
#define ADD_CO2 0x58
//CO2 sensor value
float CO2_value;
//Value to detected the breath
int LIMIT_CO2 = 700;

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];
// Color sensor
SFE_ISL29125 RGB_sensor;
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
//CO2 sensor 
Adafruit_SGP30 sgp;

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
//The cyan_color() function allows to light the bionic flower in cyan ( green and blue )
void cyan_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,255,255);
  }
  FastLED.show();
}
//The magenta_color() function allows to light the bionic flower in magenta ( red and blue )
void magenta_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,0,255);
  }
  FastLED.show();
}
//The yellow_color() function allows to light the bionic flower in yellow( green and red )
void yellow_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,255,0);
  }
  FastLED.show();
}
//The black_color() function allows to light the bionic flower in black
void black_color()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}


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

//The RGB_calibration() function allows to calibrate the RGB value for the red, green and blue color
void RGB_calibration()
{  
  // Color sensor selected 
  Wire.beginTransmission(ADD_COLOR);
  
  //Color sensor parameters
  unsigned int red_value, green_value ,blue_value;

  //Red color calibration
  Serial.println("Please, place the sensor on red color ...");
  delay(3000);
  // Read sensor values (16 bit integers)
  red_value = RGB_sensor.readRed();
  green_value = RGB_sensor.readGreen();
  blue_value = RGB_sensor.readBlue();  
  // Convert to RGB values 
  red_value = map(red_value, redlow, redhigh, 0, 255);
  green_value = map(green_value, greenlow, greenhigh, 0, 255);
  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
  // Constrain to values of 0-255
  red_value = constrain(red_value, 0, 255);
  green_value = constrain(green_value, 0, 255);
  blue_value= constrain(blue_value, 0, 255);
  Red_R= red_value;
  Red_G = green_value;
  Red_B = blue_value;
  delay(3000);

  //Green color calibration
  Serial.println("Please, place the sensor on green color ...");
  delay(3000);
  // Read sensor values (16 bit integers)
  red_value = RGB_sensor.readRed();
  green_value = RGB_sensor.readGreen();
  blue_value = RGB_sensor.readBlue();  
  // Convert to RGB values 
  red_value = map(red_value, redlow, redhigh, 0, 255);
  green_value = map(green_value, greenlow, greenhigh, 0, 255);
  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
  // Constrain to values of 0-255
  red_value = constrain(red_value, 0, 255);
  green_value = constrain(green_value, 0, 255);
  blue_value= constrain(blue_value, 0, 255);
  Green_R= red_value;
  Green_G = green_value;
  Green_B = blue_value;
  delay(3000);

  //Blue color calibration
  Serial.println("Please, place the sensor on blue color ...");
  delay(3000);
  // Read sensor values (16 bit integers)
  red_value = RGB_sensor.readRed();
  green_value = RGB_sensor.readGreen();
  blue_value = RGB_sensor.readBlue();  
  // Convert to RGB values 
  red_value = map(red_value, redlow, redhigh, 0, 255);
  green_value = map(green_value, greenlow, greenhigh, 0, 255);
  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
  // Constrain to values of 0-255
  red_value = constrain(red_value, 0, 255);
  green_value = constrain(green_value, 0, 255);
  blue_value= constrain(blue_value, 0, 255);
  Blue_R= red_value;
  Blue_G = green_value;
  Blue_B = blue_value;
  delay(3000);

  // The end of the transmission
  Wire.endTransmission();
   
     
}
//The color_sensor() function allows to read the RGB value of the color and test if it is the red, green or blue color
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
  red_value = constrain(red_value, 0, 255);
  green_value = constrain(green_value, 0, 255);
  blue_value= constrain(blue_value, 0, 255);

  Serial.print("COLOR : "); Serial.print("R "); Serial.print(red_value); Serial.print("G "); Serial.print(green_value); Serial.print("B ");Serial.println(blue_value);   

  // Test if the color detected is red, if it is the case, RED = true
  if ((red_value>Red_R-range) && ( red_value<Red_R+range)&& (green_value>Red_G-range) && ( green_value<Red_G+range)&&( blue_value>Red_B-range) && ( blue_value<Red_B+range))
  {
    RED= true;
  }
  // Test if the color detected is green, if it is the case, GREEN = true
  else if ((red_value>Green_R-range) && (red_value<Green_R+range)&& (green_value>Green_G-range) && ( green_value<Green_G+range)&&( blue_value>Green_B-range) && ( blue_value<Green_B+range))
  { 
    GREEN= true;
  }
  // Test if the color detected is blue, if it is the case, BLUE = true
  else if ((red_value> Blue_R -range) && (red_value<Blue_R+range)&& (green_value> Blue_G-range) && (green_value< Blue_G+range)&&(blue_value> Blue_B-range) && (blue_value< Blue_B+range))
  {
    BLUE= true; 
  }
  
  // The end of the transmission
  Wire.endTransmission();
   
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
 Serial.println("Diversity of the flower scenario : Task 5");
 
 ///LED initialisation
 FastLED.addLeds<NEOPIXEL,LED_PIN>(leds,NUM_LEDS);
 black_color();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 //Color sensor initialisation
 RGB_sensor.init();
 //Make the color calibration
 BW_calibration();
 RGB_calibration();

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 // CO2 sensor initialisation
 sgp.begin();

 delay(3000);
   
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{
  //Color no detected
  while ((BLUE == false) && (RED==false)&& (GREEN==false))
  {
    Read_RGB();
  }
  
  //First color detected 
  Serial.println("First color detected!");
  //Flower lights in the color which is detected
  if (RED==true) 
  { 
    red_color();
  }
  else if (BLUE == true) 
  { 
    blue_color();
  }
  else if (GREEN=true)
  {
    green_color();
  }
  //The flower is opening (50%)
  while(current_position < FLOWER_CLOSE_TO_OPEN/2)
  { 
    stepper.rotate(360);
    current_position = current_position +1;
  }

  //No new color is detected 
  while (((RED==false)&& (GREEN==false))||((BLUE==false)&& (GREEN==false)) || ((RED==false)&& (BLUE==false)))
  { 
    Read_RGB();
  }
  
   //Second color detected
   Serial.println("Second color detected!");
   
   //CO2 sensor selected 
   Wire.beginTransmission(ADD_CO2);
   // Read the CO2 value
   if (! sgp.IAQmeasure()) {return;}
   CO2_value = sgp.eCO2;
   Serial.print("eCO2 "); Serial.println(CO2_value);
   Wire.endTransmission();
   
   while(CO2_value<=LIMIT_CO2)
   {
    Wire.beginTransmission(ADD_CO2);
    if (! sgp.IAQmeasure()) {return;}
    CO2_value = sgp.eCO2;
    Serial.print("eCO2 "); Serial.println(CO2_value);
    Wire.endTransmission();
   }

   // A breath is detected 
   // The flower lights in the mixing color.
   if ((RED==true)&&(BLUE==true))
   { 
    magenta_color();
   }
   else if ((RED==true)&&(GREEN==true))
   {
    yellow_color();
   }
   else if ((GREEN==true)&&(BLUE==true))
   {
    cyan_color();
   }
   
   //The flower is fully opening 
   while(current_position < FLOWER_CLOSE_TO_OPEN)
   { 
      stepper.rotate(360);
      current_position = current_position +1;
   }
  
   
   delay(5000);

   //Return to an initial position
   //The flower is closing
   while(current_position > 0)
   { 
      stepper.rotate(-360);
      current_position = current_position -1;
   }
   //No color
   black_color();
   RED=false;
   BLUE=false;
   GREEN=false;
    
  
}
