//FOOD

//TASK 2

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED_R=13; 

//LED RGB (green)
int PIN_LED_G=16;

//Touch sensor
int PIN_TOUCH=17;

//GAME
// Number_player that determines the number of player
int Number_player=5;

//FUNCTION
//player_display: function that display the player's number
void player_display(int number)
{
  for(int i=0;i<number;i=i+1)
  { 
    //turn on the LED
    digitalWrite(PIN_LED_R, HIGH); 
    delay(400);
    
	//turn off the LED
    digitalWrite(PIN_LED_R,LOW);
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
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  
  //ESP32 receives information from the touch sensor
  pinMode(PIN_TOUCH,INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Food: task 2!");  

}

//LOOP: function that display the player's number thanks to the LED each time a contact has been detected
void loop()
{
 int player=1;
 int State_Touch;
 
 //turn on the green LED
 digitalWrite(PIN_LED_G,HIGH);
 
 while (player<=Number_player)
 {
    Serial.println("Player");
    Serial.println(player);
    player_display(player);
     do 
     {
      //Reading and display the touch value
      State_Touch=digitalRead(PIN_TOUCH);
     }
     while (State_Touch!=HIGH);
     delay(500);
     player=player+1;
 }
 
 //turn off the green LED
 digitalWrite(PIN_LED_G,LOW);
 delay(500);
}