//CYCLE OF THE DAY

//TASK 2

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

//VARIABLES
//Temperature_Limit determines the limit temperature (°C) between hot and cold
float Temperature_Limit=22; 

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup() 
 {
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED_R,OUTPUT);
  pinMode(PIN_LED_B,OUTPUT);
  //ESP32 receives information from the temperature sensor
  pinMode(PIN_TEMPERATURE,INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Cycle of the day: task 2!");  

  //Start the temperature sensor
  sensors.begin();
}

//LOOP: function that read the sensor's data and lights the red LED if it is hot or the blue LED if it is cold
 void loop()
 {
   //Reading and display the temperature (°C) 
   sensors.requestTemperatures(); 
   float Temperature_Value=sensors.getTempCByIndex(0);
   Serial.println("Temperature");
   Serial.print(Temperature_Value);
   Serial.println("ºC");

   //Hot
   if ( Temperature_Value>=Temperature_Limit)
   { 
    //Red (LED ESP32)
    digitalWrite(PIN_LED_R,HIGH); 
    digitalWrite(PIN_LED_B,LOW);
    }
   
   //Cold
   else
   {
    //Blue (LED breadboard)
    digitalWrite(PIN_LED_B,HIGH); 
    digitalWrite(PIN_LED_R,LOW);
   }
}