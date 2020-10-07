//FOOD

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED_R = /*complete with the GPIO's number*/; 

//LED RGB (green)
int PIN_LED_G =/*complete with the GPIO's number*/;

//GAME
//Number_player determines the number of player
int Number_player=/*complete with the number of the players*/;

//FUNCTION
//player_display: function that display the player's number
void player_display(int number)
{
  for(int i=0;i</*?*/;i=i+1)
  { 
    //turn on the LED
    digitalWrite(PIN_LED_R,/*complete with the LED's level*/; 
    delay(400);
    //turn off the LED
    digitalWrite(PIN_LED_R,/*complete with the LED's level*/);
    delay(400);
  }
}

//tongue_movement: function that moves the tongue to recreate an activity movement of the chameleon
void tongue_movement()
{
   /*...*/
}

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED_R,/*complete with the LED's mode*/);
  pinMode(PIN_LED_G,/*complete with the LED's mode*/);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Food!");  
}

//LOOP: function that display the player's number thanks to the LED
void loop()
{
 int player=1;
 //turn on the green LED
 digitalWrite(PIN_LED_G,/*complete with the LED's level*/);
 
 while (player<=/*?*/)
 {
    Serial.println("Player");
    Serial.println(player);
    /*call the player_display() function*/
    delay(500);
    player=player+1;
 }
 //turn off the green LED
 digitalWrite(PIN_LED_G,/*complete with the LED's level*/);
 delay(500);
}