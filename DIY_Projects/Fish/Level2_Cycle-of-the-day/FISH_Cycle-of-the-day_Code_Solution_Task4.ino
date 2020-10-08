//CYCLE OF THE DAY

//TASK 4

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

//Servomotor
int PIN_SERVO=25;

//VARIABLES
//Temperature_Limit determines the limit temperature (°C) between hot and cold
float Temperature_Limit=22; 
//Luminosity_Limit determines the limit luminosity between day and night 
int Luminosity_Limit=200; 
//Temporization determines the speed of the fish
int Temporization=500; 

//SETUP: function that initialize the components and display a start message to the serial monitor
 void setup()
 {
  //INITIALIZATION
  //ESP32 sends information to the LEDS
  pinMode(PIN_LED_R,OUTPUT);
  pinMode(PIN_LED_B,OUTPUT);
  
  //ESP32 receives information from the temperature sensor
  pinMode(PIN_TEMPERATURE,INPUT);
  
  //ESP32 receives information from the light sensor
  pinMode(PIN_LIGHT_SENSOR,INPUT);
  
  //match between servomotor and the number pin specified 
  servo.attach(PIN_SERVO);
  
  //initial value of the servomotor angle
  servo.write(90);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600);
  delay(5000);
  Serial.println("Cycle of the day: task 4!");  

  //Start the temperature sensor
  sensors.begin();
}

//LOOP: function that control a servomotor
 void loop() 
 {
   // SERVO MOVEMENT 
   // the servomotor moves to be 110° position
   servo.write(110); 
   // wait Temporization ms
   delay(Temporization); 
   // the servomotor moves to be 70° position
   servo.write(70);
    // wait Temporization ms 
   delay(Temporization);
}