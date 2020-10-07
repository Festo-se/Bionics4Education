//SWIMMING COMPETITION

//TASK 3

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32
int PIN_LED=13; 

//Touch sensor
int PIN_TOUCH=16;

//Light sensor
int PIN_LIGHT=26;

//GAME
// Number_player that determines the number of player
int Number_player=3;

//Table that determines the points can be awarded for the color
int Table_Point_Color[]={0,2,4};

//Restart allows to restart the loop function if it is true
boolean Restart=true;


//TOUCH 
//Touch variable stores the score, randomly definied by the Touch_point()function when the touch sensor is a high level
int Touch;
//Touch variable stores the score, randomly definied by the Touch_point() function when the touch sensor is a low level
int Not_Touch;

//LIGHT
//Luminosity_Limit determines the limit luminosity between day and night 
int Luminosity_Limit=200; 

//Night variable stores the score, randomly defined by the Luminosity_Poit() function when the luminosity value is lower than the Luminosity_Limit
int Night;
//Day variable stores the score, randomly defined by the Luminosity_Poit() function when the luminosity value is superior or equal than the Luminosity_Limit
int Day;

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
    digitalWrite(PIN_LED, HIGH); 
    delay(400);
	
    //turn off the LED
    digitalWrite(PIN_LED,LOW);
    delay(400);
  }
}

//Touch_Point: function that randomly assigns the points for the variables of the touch sensor
void Touch_Point()
{ 
  //0 or 1
  int a=random(2);
  if( a==0)
  {
    Touch=0;
    Not_Touch=1;
  }
  
  else
  {  
    Touch=1;
    Not_Touch=0;
  } 
}

//Luminosity_Point: function that randomly assigns the points for the variables of the light sensor
void Luminosity_Point()
{ 
  //0 or 1
  int a=random(2);
  if( a==0)
  {
    Day=0;
    Night=2;
  }
  
  else
  {  
    Day=2;
    Night=0;
  }
}

//Score_and_speed: function that allows you to associate a score with a fish speed
int Score_and_speed( int score)
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
  int maximum=0;
 /*...*/
  return maximum+1;
}

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LED
  pinMode(PIN_LED,OUTPUT);
  
  //ESP32 receives information from the touch sensor
  pinMode(PIN_TOUCH,INPUT);
  
  //ESP32 receives information from the color sensor
  pinMode(PIN_LIGHT,INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Swimming competition: task 3!");  

}

//LOOP: function that calculates the points for the touch sensor and the light sensor. Then,the function display for each player, their number and calculates their score. You can restart the game.
void loop()
{
  while (Restart==true)
  { 
   Restart=false;

   //calculation of points
   Touch_Point();
   Luminosity_Point();

   Serial.println("POINTS");
   
   Serial.println("Touch");
   Serial.println(Touch);
   Serial.println("No Touch");
   Serial.println(Not_Touch);

   Serial.println("Night");
   Serial.println(Night);
   Serial.println("Day");
   Serial.println(Day);
   
    int State_Touch;
    for (int i=1;i<=Number_player;i=i+1)
   {
        Serial.println("Player");
        Serial.println(i);
        player_display(i);
  
        do 
       {
         //Reading Touch Value
          State_Touch = digitalRead(PIN_TOUCH);
       }
       while (State_Touch!=HIGH);
       //suspens
       delay(3000);
      
       int Score=0;

       //Reading touch value
       State_Touch=digitalRead(PIN_TOUCH); 
       Serial.println("State Touch");
       Serial.println(State_Touch);

       //Reading luminosity 
       int Luminosity_Value=analogRead(PIN_LIGHT); 
       Serial.println("Light");
       Serial.println(Luminosity_Value,DEC); 

       if(State_Touch==1) 
		{
		   Score=Score+Touch;
		}
		
       else
	   {
		   Score=Score+Not_Touch;
		}

        if (Luminosity_Value<Luminosity_Limit)
       {
		   Score=Score+Night;
		}
       else
	   {
		   Score=Score+Day;
		}

       Serial.println("Score");
       Serial.println(Score);
   }

   delay(10000);
   State_Touch=digitalRead(PIN_TOUCH);
   Serial.println("RESTART");
   Serial.println(State_Touch);
   if (State_Touch==HIGH)
   {
    //The game restart
    Restart=true;
   }
  }
  
}