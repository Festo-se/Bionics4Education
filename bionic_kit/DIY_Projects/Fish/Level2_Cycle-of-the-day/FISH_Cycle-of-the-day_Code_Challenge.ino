// LED2 (built-in ESP32)
// GPIO

// RGB LED
// GPIO

// temperature sensor
// GPIO
// library
// define temperaturesensor
// set treshold for the temperature sensor. The variable determines the treshold between warm and cold (°C).

// light sensor
// GPIO
// set treshold for light sensor

// servomotor
// library
// GPIO
// PWM properties servomotor
// define servomotor angles
// define servomotor time

// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle
// convert 0-180 degrees to 0-65536

// global variables

// setup the components
void setup()
{
  // setup LED2 as OUTPUT

  // setup LED_RGB as OUTPUT

  // setup the temperature sensor as INPUT
  // start the temperaturesensor

  // setup the light sensor as INPUT

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // read and display the temperature (°C)

  // If the temperature sensor value is equal of higher then the temperature treshold print "warm" in the serial monitor.
  // flash the red LED

  // If the temperature sensor value is lower then the temperature treshold print "cold" in the serial monitor.
  // flash the blue LED

  // read the current light sensor value

  // If the light sensor value is equal of higher then the light treshold print "day" in the serial monitor.
  // set servomotor time to 1000 ms

  // If the light sensor value is lower then the light treshold print "night" in the serial monitor.
  // set servomotor time to 2000 ms
  // create a movement of the servomotor to angle max and min
}