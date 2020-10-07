//FOOD

//TASK 3

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED_R = 13; 

//LED RGB (green)
int PIN_LED_G =16;

//Touch sensor
int PIN_TOUCH = 17;

//GAME
// Number_player that determines the number of player
int Number_player=5;

// Restart allows to restart the loop function if it is true
boolean Restart=true;

//Continue allows to stop the game if the winner color was found if it is false
boolean Continue=true;

//Winner that is the winning number (randomly defined)
int Winner;


//FUNCTION
//player_display : function that display the player's number
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

//tongue_movement : function that moves the tongue to recreate an activity movement of the chameleon
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
  Serial.println("Food: task 3!");  
}

//LOOP: function that randomly definie a winning number. Then the function display the player's number thanks to the LED each time a contact has been detected. If it is the winning number the green LED light and the game is over. You can restart the game if you touch the sensor after the end of the game.
void loop()
{
  while (Restart==true)
 {  
   Restart=false;
   digitalWrite(PIN_LED_G,LOW);
   digitalWrite(PIN_LED_R,LOW);

  //definition of the winning number randomly
  //0,1,...,Number_player-1
  int rd=random(Number_player);
  //1,2,...,Number_player
  Winner=rd +1;
  Serial.println("Winner");
  Serial.println(Winner);

  int player=1;
  int State_Touch; 
  while ((Continue==true)&&(player<=Number_player))
  {
    Serial.println("Player");
    Serial.println(player);
    player_display(player);
    do 
     {
      //Reading and display the touch value
      State_Touch = digitalRead(PIN_TOUCH);
     }
	 
     while (State_Touch!=HIGH);
     //Suspens
     delay(4000);

     if (player==Winner)
     {
      Serial.println("Win");
      digitalWrite(PIN_LED_G,HIGH);
      Continue=false;
     }
     
	 else
     {
      Serial.println("Lose");
     }
	 
     delay(500);
     player=player+1;
  }
   
   //Ready to restart? 
   delay(10000);
   State_Touch = digitalRead(PIN_TOUCH);
   Serial.println("RESTART");
   Serial.println(State_Touch);
   if (State_Touch==HIGH)
   {
    //The game restart
    Restart=true;
    Continue=true;
   }
 }
}