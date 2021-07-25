/*BEE scenario */

/*Library*/
#include <Arduino.h>

/*GPIO*/
//Vibrating motor pin


/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Bee scenario : Task 1");
 
 //Define the vibrating motor as a output

 //Turn off the vibrating motor

}

/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
  //Turn on the vibrating motor
  
  delay(1000);
  //Turn off the vibrating motor    
  
  delay(1000);
}
