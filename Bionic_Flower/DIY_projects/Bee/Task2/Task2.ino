/*BEE,Task 2 : Active the vibrating motor if a magnet is detected */

/*Library*/
#include <Arduino.h>

/*GPIO*/
//Vibrating motor pin
#define MOTOR_PIN 22
//Hall sensor pin
#define HALL_PIN 21

/*Variable*/
//If a magnet is detected; Magnet = 0. Otherwise Magnet = 1
int magnet;

/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Bee scenario : Task 2");
 
 //Define the vibrating motor as a output
 pinMode(MOTOR_PIN, OUTPUT);
 //Turn off the vibrating motor
 digitalWrite(MOTOR_PIN, LOW);

 //Define the hall sensor as a imput
 pinMode(HALL_PIN,INPUT);
}

/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop() 
{   
    //Read the hall sensor
    magnet = digitalRead( HALL_PIN);
    Serial.println("Magnet");
    Serial.println(magnet);

    //a magnet is detected
    if (magnet == 0)
    {//Turn on the vibrating motor 
      digitalWrite(MOTOR_PIN,HIGH);
    }
    //a magnet isn't detected 
    else 
    { //Turn off the vibrating motor
      digitalWrite(MOTOR_PIN, LOW);
    }
}
