//Adaptability OF THE TRUNK

//TASK 4

//LIBRARY
#include <ESP32Servo.h>
Servo servo;

//GLOBALES VARIABLES
//PWM properties Servo
int Frequence0=50;
int LED_Channel0=0;
int Resolution0=16; 

//PWM properties LED
int Frequence12=5000;
int LED_Channel12=12;
int Resolution12=8;

//GPIO
int PIN_Built_in=13;
int PIN_BUZZER=17;
int PIN_TOUCH=16;
int PIN_LIGHT=26;

//VARIABLE
//Luminosity_Limit determines the limit luminosity between the day and the middle of the day 
int Limit_Day_Middle=1000;

//Luminosity_Limit determines the limit luminosity between the middle of the day and the night
int Limit_Middle_Night=200; 

//FUNCTION
//Command_servo: function that give the order of the angle to the servomotor
void Command_servo(float angle)
{   
    //convert 0-180 degrees to 0-65536
    uint32_t conv = (((angle/180.0)*2000)/20000.0*65536.0)+1634;
    ledcWrite(Channel_Servo,conv);
}

//movement_trunk : function that creates a movement of the tongue to convert a moment of activity of the chameleon
void movement_trunk()
{
  /*...*/
}

//SETUP: function that initialize the components and display a start message to the serial monitor
void setup()
{
  //INITIALIZATION
  //ESP32 sends information to the LED
  pinMode(PIN_Built_in, OUTPUT);
  
  //ESP32 sends information to the buzzer
  pinMode(PIN_BUZZER,OUTPUT);
  
  //ESP32 receives infomation from the touch sensor
  pinMode(PIN_TOUCH, INPUT);
  
  //ESP32 receives information from the light sensor
  pinMode(PIN_LIGHT,INPUT);
  ledcAttachPin(PIN_Built_in,LED_Channel12);
  ledcSetup(LED_Channel12, Frequence12, Resolution12);
  ledcAttachPin(PIN_SERVOS,LED_Channel0);
  ledcSetup(LED_Channel0,Frequence0,Resolution0);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600); 
  delay(5000);
  Serial.println("Adapatability of the trunk: task 4!"); 

}

//LOOP: function that read the light value. If it is daytime, the elephant communicates with you: every time you press the sensor to touch a sound is created. If it is the middle of the day, nothing happens. If it is night, the led creates a snoring. - code executed repeatedly
void loop()
{  
    //Reading and diplay the ligth sensor value
   int Light_Value = analogRead(PIN_LIGHT);
   Serial.println("Light value");
   Serial.println(Light_Value,DEC);

   //DAY
   if ( Light_Value >= Limit_Day_Middle)
   { 
    Serial.println("Day");
    ledcWrite(LED_Channel12,256);

    //Reading and display the touch value
   int State_Touch = digitalRead(PIN_TOUCH);
   Serial.printn("State touch");
   Serial.println(State_Touch);
   
     if(State_Touch==HIGH)
     {
       //Create a noise
       for (int i = 0; i <20; i++) 
       {
        digitalWrite (PIN_BUZZER, HIGH) ;
        delay (2);
        digitalWrite (PIN_BUZZER, LOW) ;
        delay (2);
       }
     }
   }

   //NIGHT
   else if (Light_Value<=Limit_Middle_Night)
   {
     Serial.println("Night");
     
	 //Snoring
     for (int i=0;i<=256;i=i+10) 
     { 
     ledcWrite(LED_Channel12,i); 
     delay(50);
     }
	 
     for (int y=256;y>=0;y=y-10) 
     {  
     ledcWrite(LED_Channel12,y);
     delay(50); 
     }
   }

   //MIDDLE 
   else
   {
      Serial.println("Middle");
   }
   delay(500);
}