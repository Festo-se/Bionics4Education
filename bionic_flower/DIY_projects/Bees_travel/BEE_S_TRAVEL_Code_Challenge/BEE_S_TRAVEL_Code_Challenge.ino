/*Bee's travel, Task 1: Change the flower's color .*/

/*Library*/
#include <Arduino.h>
// LED's library


/*GPIO*/
//LED pin


/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
////Address of the color sensor
//
//// R G B value for the white color
//unsigned int redhigh , greenhigh, bluehigh;
//// R G B value for the black color
//unsigned int redlow, greenlow, bluelow;
//// R G B value for the red color
//int Red_R, Red_G, Red_B;
//// R G B value for the green color
//int Green_R, Green_G, Green_B;
//// R G B value for the blue color
//int Blue_R, Blue_G, Blue_B;
//// R G B value for the path 
//int Path_R, Path_G, Path_B;
//// R G B value for the end of the path
//int End_R, End_G, End_B;
//// RED = true if the red color is detected, otherwise false
//boolean RED = false ;
//// GREEN = true if the green color is detected, otherwise false
//boolean GREEN = false;
//// BLUE = true if the blue color is detected, otherwise false
//boolean BLUE = false;
////Range (a margin of error for the RGB value) 
//int range = 10;


/*Obejct*/
//LED


/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/

////The calibration_color() function allows to calibrate the high (white) and the low (black) value 
//void BW_calibration()
//{  
//   // Color sensor selected, start the transmission
//   Wire.beginTransmission(ADD_COLOR);
//
//   //White color calibration
//   Serial.println("Please, place the sensor on white color ...");
//   delay(3000);
//   redhigh = RGB_sensor.readRed();
//   greenhigh = RGB_sensor.readGreen();
//   bluehigh = RGB_sensor.readBlue();
//   delay(3000);
//   
//   //Black color calibration
//   Serial.println("Please, place the sensor on black color ...");
//   delay(3000);
//   redlow = RGB_sensor.readRed();
//   greenlow = RGB_sensor.readGreen();
//   bluelow = RGB_sensor.readBlue();
//   delay(3000);
//
//    // The end of the transmission
//    Wire.endTransmission();
//}
//
////The RGB_calibration() function allows to calibrate the RGB value for the red, green and blue color
//void RGB_calibration()
//{  
//  // Color sensor selected 
//  Wire.beginTransmission(ADD_COLOR);
//  
//  //Color sensor parameters
//  unsigned int red_value, green_value ,blue_value;
//
//  //Red color calibration
//  Serial.println("Please, place the sensor on red color ...");
//  delay(3000);
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//  Red_R= red_value;
//  Red_G = green_value;
//  Red_B = blue_value;
//  delay(3000);
//
//  //Green color calibration
//  Serial.println("Please, place the sensor on green color ...");
//  delay(3000);
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//  Green_R= red_value;
//  Green_G = green_value;
//  Green_B = blue_value;
//  delay(3000);
//
//  //Blue color calibration
//  Serial.println("Please, place the sensor on blue color ...");
//  delay(3000);
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//  Blue_R= red_value;
//  Blue_G = green_value;
//  Blue_B = blue_value;
//  delay(3000);
//
//   //Path calibration
//  Serial.println("Please, place the sensor on the path ...");
//  delay(3000);
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//  Path_R= red_value;
//  Path_G = green_value;
//  Path_B = blue_value;
//  delay(3000);
//
//   //The end calibration
//  Serial.println("Please, place the sensor on the end of the path ...");
//  delay(3000);
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//  End_R= red_value;
//  End_G = green_value;
//  End_B = blue_value;
//  delay(3000);
//
//  // The end of the transmission
//  Wire.endTransmission();
//   
//     
//}
////The color_sensor() function allows to read the RGB value of the color and test if it is the red, green or blue color
//void Read_RGB()
//{ 
//  // Color sensor selected 
//  Wire.beginTransmission(ADD_COLOR);
//  
//  //Color sensor parameters
//  unsigned int red_value, green_value ,blue_value;
//
//  // Read sensor values (16 bit integers)
//  red_value = RGB_sensor.readRed();
//  green_value = RGB_sensor.readGreen();
//  blue_value = RGB_sensor.readBlue();  
//  // Convert to RGB values 
//  red_value = map(red_value, redlow, redhigh, 0, 255);
//  green_value = map(green_value, greenlow, greenhigh, 0, 255);
//  blue_value = map(blue_value, bluelow, bluehigh, 0, 255);  
//  // Constrain to values of 0-255
//  red_value = constrain(red_value, 0, 255);
//  green_value = constrain(green_value, 0, 255);
//  blue_value= constrain(blue_value, 0, 255);
//
//  Serial.print("COLOR : "); Serial.print("R "); Serial.print(red_value); Serial.print("G "); Serial.print(green_value); Serial.print("B ");Serial.println(blue_value);   
//
//  // Test if the color detected is red, if it is the case, RED = true
//  if ((red_value>Red_R-range) && ( red_value<Red_R+range)&& (green_value>Red_G-range) && ( green_value<Red_G+range)&&( blue_value>Red_B-range) && ( blue_value<Red_B+range))
//  {
//    RED= true;
//  }
//  // Test if the color detected is green, if it is the case, GREEN = true
//  else if ((red_value>Green_R-range) && (red_value<Green_R+range)&& (green_value>Green_G-range) && ( green_value<Green_G+range)&&( blue_value>Green_B-range) && ( blue_value<Green_B+range))
//  { 
//    GREEN= true;
//  }
//  // Test if the color detected is blue, if it is the case, BLUE = true
//  else if ((red_value> Blue_R -range) && (red_value<Blue_R+range)&& (green_value> Blue_G-range) && (green_value< Blue_G+range)&&(blue_value> Blue_B-range) && (blue_value< Blue_B+range))
//  {
//    BLUE= true; 
//  }
//  // Test if the sensor is on the path, if it is the case, PATH = true
//
//  
//  // Test if the sensor is on the end of the path , if it is the case, END = true
//  
//  
//  // The end of the transmission
//  Wire.endTransmission();
//   
//}


/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Bee's travel scenario : Task 1");
 
 ///LED initialisation
 
 //Turn off the LEDs
 
     
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  
   //The flower light in random color 
  
  //Wait 500 ms
 
  
}
