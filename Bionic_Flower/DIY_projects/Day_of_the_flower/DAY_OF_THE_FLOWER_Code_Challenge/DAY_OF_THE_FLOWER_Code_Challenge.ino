/*DAY OF THE FLOWER,Task 1 : Change the LED's color .  */

/*Library*/
#include <Arduino.h>
// LED's library


/*GPIO*/
//LED pin


/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5

/*Obejct*/
//LED
CRGB leds[NUM_LEDS];




/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Day of the flower : Task 1");

 //LED initialisation
 

}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{
  //Turn on the LEDs in the color used for the night
  
  delay(500);
  //Turn on the LEDs in the color used for the morning
 
  delay(500);
  //Turn on the LEDs in the color used for the day
  
  delay(500);
  
}
