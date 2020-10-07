//CYCLE OF THE DAY

//TASK 3

//LIBRARY
#include <ESP32Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Temperature sensor
int PIN_TEMPERATURE=17;
OneWire oneWire(PIN_TEMPERATURE);
DallasTemperature sensors(&oneWire);

//servomotor
Servo servo; 

//GLOBALES VARIABLES
//GPIO 
//LED built-in ESP32

int PIN_LED_R=13; 
//LED RGB (breadboard)

int PIN_LED_B=16;

// Light sensor
int PIN_LIGHT_SENSOR=26;

//VARIABLES
//Temperature_Limit determines the limit temperature (°C) between hot and cold
float Temperature_Limit=22;

//Luminosity_Limit determines the limit luminosity between day and night 
int Luminosity_Limit=200; 

//SETUP: function that initialize the components and display a start message to the serial monitor
void setup()
{
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  
  //ESP32 receives information from the temperature sensor
  pinMode(PIN_TEMPERATURE,INPUT);
  
  //ESP32 receives information from the light sensor
  pinMode(PIN_LIGHT_SENSOR,INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Cycle of the day: task 3!");  

  // Start the temperature sensor
  sensors.begin();
}

//LOOP: function that read the temperature value and lights the red LED if it is hot or the blue LED if it is cold. In addition, the loop function read the light value and display "Day" if it is the day or "Night" if it is the night.
 void loop() 
 {
   //Reading and display the temperature (°C) 
   sensors.requestTemperatures(); 
   float Temperature_Value=sensors.getTempCByIndex(0);
   Serial.println("Temperature");
   Serial.print(Temperature_Value);
   Serial.println("ºC");

   //Reading and display the luminosity
   int Luminosity_Value=analogRead(PIN_LIGHT_SENSOR); 
   Serial.println("Light");
   Serial.println(Luminosity_Value,DEC); 

   //Hot
   if ( Temperature_Value>=Temperature_Limit)
   { 
    //Red (LED ESP32)
    digitalWrite(PIN_LED_R,HIGH); 
    digitalWrite(PIN_LED_B,LOW);
    }
   
   //Cold
   else {
    //Blue (LED breadboard)
    digitalWrite(PIN_LED_B,HIGH); 
    digitalWrite(PIN_LED_R,LOW);
    }

   //Day
   if ( Luminosity_Value>=Luminosity_Limit)
   { 
    Serial.println("Day");
   }
   
   //Night
   else {
   Serial.println("Night");
   }
}