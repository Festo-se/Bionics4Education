//COLORED FRUIT

//TASK 1

//LIBRARY
#include <ESP32Servo.h>
Servo servo_clamps; 
Servo servo_trunk;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED=13; 

//GAME
//Number_player determines the number of player, the 3 players match the three colors
int Number_player=3;

//Restart allows to restart the loop function if it is true
boolean Restart=true;

//Continue allows to stop the game if the winner color was found if it is false
boolean Continue=true;

//VARIABLE
//Blue variable stores the blue frequency 
int Blue=7;

//Green variable stores the green frequency 
int Green=4;

//Red variable stores the red frequency 
int Red=9 ;
int table_color[]= {Blue,Green,Red};

//FUNCTION
//player_display: function that display the player's number
void player_display(int number)
{
  for(int i=0;i<number;i=i+1)
  { 
    //turn on the LED
    digitalWrite(PIN_LED, HIGH); 
    delay(400);
    
	//turn off the LED
    digitalWrite(PIN_LED,LOW);
    delay(400);
  }
}

//disgust_movement: function that moves the trunk to recreate a disgust movement
void disgust_movement()
{
   /*...*/
}

//winner_movement : function that moves the trunk to recreate a excitement movement
void winner_movement()
{
  /*...*/
}

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LED
  pinMode(PIN_LED,OUTPUT);

  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Coloured fruit: task 1!");  
}

//LOOP: function that display the player's number thanks to the LED
void loop()
{
  while (Restart==true)
 {  
    Restart=false;
    int player=1;
    while ((Continue==true)&&(player<=Number_player))
    {
     Serial.println("Player");
     Serial.println(player);
     player_display(player);
     player=player+1;
     delay(1000);
     }
  }
}