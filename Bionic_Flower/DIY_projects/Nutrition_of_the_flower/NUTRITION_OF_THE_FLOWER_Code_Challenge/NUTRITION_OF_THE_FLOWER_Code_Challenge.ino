/*Nutrition of the flower , Task 1 : Open and close the bionic flower */

/*Library*/
#include <Arduino.h>
// motor's library


/*GPIO*/
//Motor pin 
#define DIR 33
#define STEP 25
#define SLEEP 13

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

/*Obejct*/
//Motor




/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Nutrition of the flower scenario : Task 1");

 //Motor of the bionic flower initialisation


}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{
 //the flower is opening 


 //wait 1s
 
 //the fower is closing 
  
}
