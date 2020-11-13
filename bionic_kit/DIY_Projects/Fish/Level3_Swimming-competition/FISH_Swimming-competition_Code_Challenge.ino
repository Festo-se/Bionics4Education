//SWIMMING COMPETITION

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED =/*complete with the GPIO's number*/; 

//GAME
//Number_player that determines the number of player
int Number_player=/*complete with the number of player*/;

//Table that determines the points can be awarded for the color
int Table_Point_Color[]={0,2,4};

//COLOR
//Blue variable stores the blue frequency 
int Blue_Frequency=6;

//Green variable stores the green frequency 
int Green_Frequency=4;

//Red variable stores the red frequency 
int Red_Frequency=7;

//FUNCTION
//player_display: function that display the player's number
void player_display(int number)
{
  for(int i=0;i<number;i=i+1)
  { 
    //turn on the LED
    digitalWrite(PIN_LED,/*complete with the LED's level*/);
    delay(400);
	
    //turn off the LED
    digitalWrite(PIN_LED,/*complete with the LED's level*/);
    delay(400);
  }
}

//Touch_Point: function that randomly assigns the points for the variables of the touch sensor
void Touch_Point()
{
  /*...*/
}

//Luminosity_Point: function that randomly assigns the points for the variables of the light sensor
void Luminosity_Point()
{
  /*...*/  
}

//Color_Point: function that randomly assigns the points for the variables of the color sensor
//void Color_Point()

//Score_and_speed: function that allows you to associate a score with a fish speed
int Score_and_speed(int score)
{
  //Score 0-7
  switch (score)
  {
  case 0:
     return 0;
     break;
  case 1: 
    return 2000;
    break;
  case 2: 
    return 1600;
    break;
  case 3: 
    return 1400;
    break;
  case 4: 
    return 1200;
    break;
  case 5: 
    return 800;
    break;
  case 6:
    return 500;
    break;
  case 7:
    return 300;
    break;
  }
}

//max_score: function that returns the maximum score. If there is egality, the winner is randomly definied
int max_score ( int L[])
{
 /*...*/
}

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LED
  pinMode(PIN_LED,/*complete with the LED's mode*/);

  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Swimming competition!");  
}

//LOOP: function that display the player's number thanks to the LED
void loop()
{
  for (int i=1;i<=/*?*/Number_player;i=i+1)
 {
      Serial.println("Player");
      Serial.println(i);
      /*call the player_display()function*/
      delay(1000);
 }
}