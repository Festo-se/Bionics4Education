//COLORED FRUIT

//TASK 5

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

//Servomotors
int PIN_SERVO_TRUNK=17;
int PIN_SERVO_CLAMPS=26;

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
     //SERVO MOVEMENT 
     //the servo goes to one side
     servo_trunk.write(140); 
     delay(500);
     
	 //clamps open
     servo_clamps.write(40);
     delay(2000);
     
	 //the servo goes to the initial position
     servo_trunk.write(90); 
     delay(2000); 
}

//winner_movement: function that moves the trunk to recreate a excitement movement
void winner_movement()
{
  for (int i=0;i<4;i=i+1)
  {
     //SERVO MOVEMENT 
     //the servo goes to one side
     servo_trunk.write(130); 
     delay(400); 
     
	 //the servo goes to other side
     servo_trunk.write(60); 
     delay(400); 
  }
   //the servo goes to the initial position
   servo_trunk.write(90); 
   delay(2000);  
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
  
  //match between servo motor and the number pin specified 
  servo_trunk.attach(PIN_SERVO_TRUNK);
  servo_clamps.attach(PIN_SERVO_CLAMPS);
 
 //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println(" Coloured fruit: task 5!");  
}

//LOOP: function that randomly definie a winning color. Then the function display the player's number thanks to the LED and read the color sensor value each time a contact has been detected. If it is the winning color the LED light, the trunk moves with winner_movement() function and the game is over. If it is not, the trunl moves with the disgust_movement() function. You can restart the game if you touch the sensor after the end of the game.
void loop()
{
  while (Restart==true)
 {  
   Restart=false;
   //turn off the LED
   digitalWrite(PIN_LED,LOW);
   
   //Initial position for the servomotor
   servo_clamps.write(40);
   servo_trunk.write(90);
   
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
     Serial.println("Player");
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
     delay(1000);
     
	 //clamps take the object (clamps close)
     servo_clamps.write(115);

     //Reading and display the color 
     int Current_Frequency = pulseIn(PIN_COLOR, HIGH); 
     Serial.println("Color Frequency");
     Serial.println(Current_Frequency);

     //Suspens
     delay(4000);
     if ( Current_Frequency==Winner)
      { 
        //turn on LED 
        digitalWrite(PIN_LED, HIGH);
        Serial.println("Win");
        Continue = false;
        winner_movement();
      }
      else
	  {
        Serial.println("Lose");
        disgust_movement();
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