// LED2 (built-in ESP32)
// GPIO
#define LED2 13

// RGB LED
// GPIO
#define LED_RGB_Blue 16

// temperature sensor
// GPIO
#define temperaturesensor 17
// library
#include <OneWire.h>
#include <DallasTemperature.h>
// define temperaturesensor
OneWire oneWire(temperaturesensor);
DallasTemperature sensors(&oneWire);
// set treshold for the temperature sensor. The variable determines the treshold between warm and cold (°C).
float temperatureTreshold = 22;

// light sensor
// GPIO
#define lightsensor 26
// set treshold for light sensor
int lightTreshold = 4000;

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
// define servomotor time
unsigned long servo_time = 1000;

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
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup LED_RGB as OUTPUT
  pinMode(LED_RGB_Blue, OUTPUT);

  // setup the temperature sensor as INPUT
  pinMode(temperaturesensor, INPUT);
  // start the temperaturesensor
  sensors.begin();

  // setup the light sensor as INPUT
  pinMode(lightsensor, INPUT);

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
    // flash the red LED
    digitalWrite(LED2, HIGH);
    digitalWrite(LED_RGB_Blue, LOW);
    delay(500);
  }
  // If the temperature sensor value is lower then the temperature treshold print "cold" in the serial monitor.
  else {
    Serial.println("cold");
    // flash the blue LED
    digitalWrite(LED2, LOW);
    digitalWrite(LED_RGB_Blue, HIGH);
    delay(500);
  }

  // read the current light sensor value
  int lightsensor_value = analogRead(lightsensor);
  sprintf(serialprint_buffer, "Light sensor value: %d", lightsensor_value);
  Serial.println(serialprint_buffer);

  // If the light sensor value is equal of higher then the light treshold print "day" in the serial monitor.
  if (lightsensor_value >= lightTreshold) {
    Serial.println("day");
    // set servomotor time to 1000 ms
    servo_time = 1000;
  }

  // If the light sensor value is lower then the light treshold print "night" in the serial monitor.
  else {
    Serial.println("night");
    // set servomotor time to 2000 ms
    servo_time = 2000;
  }
  // create a movement of the servomotor to angle max and min
  command_servomotor(servomotor_Angle_Max);
  delay(servo_time);
  command_servomotor(servomotor_Angle_Min);
  delay(servo_time);
}