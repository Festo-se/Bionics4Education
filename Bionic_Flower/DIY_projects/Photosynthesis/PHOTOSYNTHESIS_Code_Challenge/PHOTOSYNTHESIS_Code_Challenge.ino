2/*PHTOTOSYNTHESIS, Task 1 : Change the LED's color . */

/*Library*/
#include <Arduino.h>
// LED's library


/*GPIO*/
//LED pin


/*Variable*/
//Number of the LEDs
#define NUM_LEDS 5
/*Variable*/
// Number of colors ( red, blue, green, yellow)

// Value of the flower's color ( Red =0, Blue = 1, Green =2, Yellow= 3)
int color;

/*Obejct*/
//LED



/* ************************************************************************/
/* ***************************** SETUP FUNCTION ***************************/
/* ************************************************************************/
void setup() 
{
 //Serial monitor communication
 Serial.begin(9600);
 Serial.println("Photosynthesis : Task 1");

 //LED initialisation


  //color initialisation
  color = 0;
}


/* ************************************************************************/
/* ***************************** LOOP FUNCTION ****************************/
/* ************************************************************************/
void loop()
{
   
    color= color+1;     
   // Change the flower's color
   

   //Wait 2s

}
