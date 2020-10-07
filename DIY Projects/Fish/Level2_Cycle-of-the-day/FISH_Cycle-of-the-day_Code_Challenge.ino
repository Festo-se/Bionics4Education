//CYCLE OF THE DAY

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
int PIN_LED_B=/*complete with the GPIO's number*/; 

//SETUP: function that initialize the components and display a start message to the serial monitor
void setup()
{
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED_R,/*complete with the LED's mode*/);
  pinMode(PIN_LED_B,/*complete with the LED's mode*/);
 
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Cycle of the day!");  

  //Start the temperature sensor
  sensors.begin();
}

//LOOP: function that create a color sequence : red, blue, red, blue, ...
void loop()
{
    //Red (LED ESP32)
    digitalWrite(PIN_LED_R,/*complete with the LED's level*/); 
    digitalWrite(PIN_LED_B,/*complete with the LED's level*/);
    delay(500);
    
    //Blue (LED breadboard)
    digitalWrite(PIN_LED_B,/*complete with the LED's level*/); 
    digitalWrite(PIN_LED_R,/*complete with the LED's level*/);
    delay(500);
}