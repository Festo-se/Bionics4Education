//COLORED FRUIT

//TASK 4

//LIBRARY
#include <ESP32Servo.h>
Servo servo_clamps; 
Servo servo_trunk;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED=13; 

//Touch sensor
int PIN_TOUCH=16;

//Color sensor
int PIN_COLOR=25;

//GAME
//Number_player determines the number of player, the 3 players match the three colors
int Number_player=3;

//Restart allows to restart the loop function if it is true
boolean Restart=true;

//Continue allows to stop the game if the winner color was found if it is false
boolean Continue=true;

//Winner that is the winning color (randomly defined)
int Winner;

//VARIABLE
//Blue variable stores the blue frequency 
int Blue=7;

//Green variable stores the green frequency 
int Green=4;

//Red variable stores the red frequency 
int Red=9;
int table_color[]={Blue,Green,Red};

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

//winner_movement: function that moves the trunk to recreate a excitement movement
void winner_movement()
{
  /*...*/
}

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED, OUTPUT);
  
  //ESP32 receives information from the touch sensor
  pinMode(PIN_TOUCH, INPUT);
  
  //ESP32 receives information from the color sensor
  pinMode(PIN_COLOR,INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println(" Coloured fruit : task 4!");  
}

//LOOP: function that randomly definie a winning color. Then the function display the player's number thanks to the LED and read the color sensor value each time a contact has been detected. If it is the winning color the LED light and the game is over. You can restart the game if you touch the sensor after the end of the game
void loop()
{
  while (Restart==true)
 {  
   Restart=false;
   digitalWrite(PIN_LED,LOW);
   
   //Determine the winning color
   //0,1 or 2
   int rd=random(Number_player);
   Winner=table_color[rd];
   Serial.println("Winner");
   Serial.println(Winner);
   int player=1;
   int State_Touch; 
   while ((Continue==true)&&(player<=Number_player))
    {
     Serial.println("Player ");
     Serial.println(player);
     player_display(player);
     do 
     {
      //Reading Touch Value
      State_Touch=digitalRead(PIN_TOUCH);
      Serial.println("Touch state");
      Serial.println(State_Touch);
     }
     while (State_Touch!=HIGH);
     //Reading and display the color 
     int Current_Frequency=pulseIn(PIN_COLOR, HIGH); 
     Serial.println("Color Frequency");
     Serial.println(Current_Frequency);
     if ( Current_Frequency==Winner)
      { 
        //turn on LED 
        digitalWrite(PIN_LED, HIGH);
        Serial.println("Win");
        Continue = false;
      }
      else
	  {
        Serial.println("Lose");
      }
     player=player+1;
     delay(2000);
    }

   //Ready to restart? 
   delay(10000);
   State_Touch=digitalRead(PIN_TOUCH);
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