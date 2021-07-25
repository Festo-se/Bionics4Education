/*BEE,Task 1 : Active the vibrating motor  */

/*Library*/
#include <Arduino.h>

/*GPIO*/
//Vibrating motor pin
#define MOTOR_PIN 22

/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Bee scenario : Task 1");
 
 //Define the vibrating motor as a output
 pinMode(MOTOR_PIN, OUTPUT);
 //Turn off the vibrating motor
 digitalWrite(MOTOR_PIN, LOW);
}

/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
  //Turn on the vibrating motor
  digitalWrite(MOTOR_PIN,HIGH);
  delay(1000);
  //Turn off the vibrating motor    
  digitalWrite(MOTOR_PIN, LOW);
  delay(1000);
}
