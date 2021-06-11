/* Hi ! This example will teach you how to use the bionic flower motor. The motor allows to open and close the flower.*/

//MOTOR'S LIBRARY 
#include "BasicStepperDriver.h"

//MOTOR GPIO
#define DIR 33
#define STEP 25
#define SLEEP 13
//MOTOR CHARACTERISTIC 
//1.8 degree/step
#define MOTOR_STEPS 200 
#define MICROSTEPS 1

//OBJECT CREATION : MOTOR  
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

//MOTOR VARIABLE
//speed
int RPM=240; 
//number of turns to go from state: full close to full open
int FLOWER_CLOSE_TO_OPEN = 120;
//position of the motor between full open and full close 
int current_position; 


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
   //initialise the motor
   stepper.begin(RPM, MICROSTEPS);
   motor_calibration();    
}

void loop() {
   //the flower is opening 
   while(current_position < FLOWER_CLOSE_TO_OPEN)
    { 
      stepper.rotate(360);
      current_position = current_position +1;
    }
   //the fower is closing 
   while (current_position > 0) 
   {
    stepper.rotate(-360);
    current_position = current_position -1;
   }
   
 }
