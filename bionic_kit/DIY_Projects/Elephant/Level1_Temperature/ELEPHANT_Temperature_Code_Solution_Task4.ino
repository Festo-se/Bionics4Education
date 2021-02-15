// RGB LED Blue
// GPIO
#define LED_RGB_Blue 16

// RGB LED Red
// GPIO
#define LED_RGB_Red 17

// temperature sensor
// GPIO
#define temperaturesensor 26
// library
#include <OneWire.h>
#include <DallasTemperature.h>
// define temperaturesensor
OneWire oneWire(temperaturesensor);
DallasTemperature sensors(&oneWire);
// set treshold for the temperature sensor. The variable determines the treshold between warm and cold (°C).
float temperatureTreshold = 22;

// servomotor
// library
#include <ESP32_Servo.h>
// GPIO
#define servomotor 25
// PWM properties servomotor
int servomotor_Channel = 0;
int servomotor_Frequency = 50;
int servomotor_Resolution = 16;
// define servomotor angles
int servomotor_Angle_Min = 80;
int servomotor_Angle_Max = 120;

// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle
void command_servomotor(float servomotor_Angle)
{
  // convert 0-180 degrees to 0-65536
  uint32_t conv = (((servomotor_Angle / 180.0) * 2000) / 20000.0 * 65536.0) + 1634;
  ledcWrite(servomotor_Channel, conv);
}

// global variables
char serialprint_buffer[100];

// setup the components
void setup()
{
  // setup LED_RGB_Blue as OUTPUT
  pinMode(LED_RGB_Blue, OUTPUT);

  // setup LED_RGB_Red as OUTPUT
  pinMode(LED_RGB_Red, OUTPUT);

  // setup the temperature sensor as INPUT
  pinMode(temperaturesensor, INPUT);
  // start the temperaturesensor
  sensors.begin();

  // setup servomotor as OUTPUT
  pinMode(servomotor, OUTPUT);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(servomotor, servomotor_Channel);
  // define the PWM functionalities of the channel
  ledcSetup(servomotor_Channel, servomotor_Frequency, servomotor_Resolution);

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // read and display the temperature (°C)
  sensors.requestTemperatures();
  float temperature_value = sensors.getTempCByIndex(0);
  sprintf(serialprint_buffer, "Temperature: %.2f °C", temperature_value);
  Serial.println(serialprint_buffer);

  // If the temperature sensor value is equal of higher then the temperature treshold print "warm" in the serial monitor.
  if (temperature_value >= temperatureTreshold) {
    Serial.println("warm");
	// flash the red LED with digitalWrite()
    digitalWrite(LED_RGB_Blue, LOW);
    digitalWrite(LED_RGB_Red, HIGH);
    delay(100);
  }

  // If the temperature sensor value is lower then the temperature treshold print "cold" in the serial monitor.
  else {
    Serial.println("cold");
    // flash the blue LED with digitalWrite()
    digitalWrite(LED_RGB_Blue, HIGH);
    digitalWrite(LED_RGB_Red, LOW);
    // create a movement of the servomotor to angle max and min
    command_servomotor(servomotor_Angle_Max);
    delay(1000);
    command_servomotor(servomotor_Angle_Min);
    delay(1000);
  }
}