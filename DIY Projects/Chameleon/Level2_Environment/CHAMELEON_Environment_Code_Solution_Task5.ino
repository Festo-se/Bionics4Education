//ENVIRONMENT

//TASK 5

//LIBRARY
#include <ESP32Servo.h>
Servo servo;
int PIN_SERVO=25;

//GLOBALES VARIABLES
//PWM properties Servo
int Frequence_Servo=50;
int Channel_Servo=0;
int Resolution_Servo=16; 

//PWM properties LED
int Frequence_LED=5000;
int Channel_LED=12;
int Resolution_LED=8;

//GPIO
int PIN_LED_R=13;
int PIN_LED_B=16; 
int PIN_LIGHT=26;

//associate with a vibrator motor
int PIN_TOUCH=17;  

//VARIABLES
//Luminosity_Limit determines the limit luminosity between day and night 
int Luminosity_Limit=400;

//FUNCTION
//Command_servo: function that give the order of the angle to the servomotor
void Command_servo(float angle)
{   
    //convert 0-180 degrees to 0-65536
    uint32_t conv = (((angle/180.0)*2000)/20000.0*65536.0)+1634;
    ledcWrite(Channel_Servo,conv);
}

//movement_tongue: function that creates a movement of the tongue to convert a moment of activity of the chameleon
void movement_tongue()
{
   Command_servo(120);
   delay(1000);
   Command_servo(80);
   delay(1000);
}

//SETUP: function that initialize the components and display a start message to the serial monitor
void setup()
 {
  //INITIALIZATION
  //EPS32 sends information to the LEDs
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_B,OUTPUT);
  
  //ESP32 receives information from the light sensor
  pinMode(PIN_LIGHT,INPUT);
  
  //ESP32 sends information to the servomotor
  pinMode(PIN_SERVO,OUTPUT);
  
  //ESP32 receives information from the touch sensor
  pinMode(PIN_TOUCH,INPUT);
  
  //LED's initialization
  ledcAttachPin(PIN_LED_B,Channel_LED);
  ledcSetup(Channel_LED, Frequence_LED, Resolution_LED);

  //Servomotor's initialization
  ledcAttachPin(PIN_SERVO,Channel_Servo);
  ledcSetup(Channel_Servo,Frequence_Servo,Resolution_Servo);
  
  //Initial position
  Command_servo(80);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Environment : task 5!"); 
}

//LOOP: function that read and display the touch sensor's value. If the touch value is a low level, the function read and display the light value, if it is the day the red LED is on and the tongue moves, if not the blue LED create a snoring. If the touch value is a high level, the red light flashes to indicate a danger(predator) - code executed repeatedly
void loop()
{ 
  //Reading an display the touch sensor's value
  int  State_Touch=digitalRead(PIN_TOUCH);
  Serial.println("State touch");
  Serial.println(State_Touch);
  while(State_Touch!=HIGH)
  {
    //Reading and display the light value
    int Luminosity_Value=analogRead(PIN_LIGHT);
    Serial.println("Light value");
    Serial.println(Luminosity_Value,DEC);
  
    //Day
    if (Luminosity_Value>=Luminosity_Limit)
    { 
      //Red light
      digitalWrite(PIN_LED_R,HIGH);
      ledcWrite(Channel_LED,0);
      movement_tongue();
    }
    
    //Night
    else {
      //Snoring with the blue LED
      digitalWrite(PIN_LED_R,LOW);
      for (int i=0;i<=256;i=i+10) 
      { 
       ledcWrite(Channel_LED,i); 
       delay(50);
      }
	  
      for (int y=256;y>=0;y=y-10) 
      { 
       ledcWrite(Channel_LED,y);
       delay(50); 
      }
    }
    State_Touch=digitalRead(PIN_TOUCH);
  }

  //Danger
  Serial.println("Danger");
  ledcWrite(Channel_LED,0);
  digitalWrite(PIN_LED_R,HIGH);
  delay(300);
  digitalWrite(PIN_LED_R,LOW);
  delay(300);
}