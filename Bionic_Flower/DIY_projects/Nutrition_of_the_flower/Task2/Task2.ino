/*Nutrition, Task 2 : Open the flower is the day and close the flower is the night */

/*Library*/
#include <Arduino.h>
// motor's library
#include "BasicStepperDriver.h"
// I2C communication library
#include <Wire.h>
// light sensor's library
#include "RPR-0521RS.h"

/*GPIO*/
//Motor pin 
#define DIR 33
#define STEP 25
#define SLEEP 13
//I2C communication pin 
#define I2C_SDA 21
#define I2C_SCL 22

/*Variable*/
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
//Luminosity sensor
uint8_t luminosity_sensor;
//Proximity value
uint32_t proximity;
//Luminosity value
float luminosity;
// Limit between day and night (depend on the ambiant luminosity)
float luminosity_limit = 400;

/*Obejct*/
//Motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);
//Light sensor 
RPR0521RS rpr0521rs;

/* ************************************************************************/
/* ****************************** FUNCTION ********************************/
/* ************************************************************************/
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
 Serial.println("Nutrition of the flower scenario : Task 2");

 //Motor of the bionic flower initialisation
 stepper.begin(RPM, MICROSTEPS);   
 motor_calibration();

 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
 // Light sensor initialisation
 luminosity_sensor = rpr0521rs.init();

}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{  
  //Read the luminosity value
 luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
 Serial.println("Luminosity value");
 Serial.println(luminosity);

 //Day
 while (luminosity >= luminosity_limit)
 {
   //the flower is opening 
   if(current_position < FLOWER_CLOSE_TO_OPEN)
    { 
      stepper.rotate(360);
      current_position = current_position +1;
    }
    //Read the luminosity value
     luminosity_sensor= rpr0521rs.get_psalsval(&proximity,&luminosity);
     Serial.println("Luminosity value");
     Serial.println(luminosity);
 } 
   //No the day = Night 
   //the fower is closing 
   if(current_position > 0) 
   {
    stepper.rotate(-360);
    current_position = current_position -1;
   }

}
