// RGB LED Blue
// GPIO

// RGB LED Red
// GPIO

// temperature sensor
// GPIO
// library
// define temperaturesensor
// set treshold for the temperature sensor. The variable determines the treshold between warm and cold (°C).

// servomotor
// library
// GPIO
// PWM properties servomotor
// define servomotor angles

// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle
// convert 0-180 degrees to 0-65536

// global variables

// setup the components
void setup()
{
  // setup LED_RGB_Blue as OUTPUT
 
  // setup LED_RGB_Red as OUTPUT

  // setup the temperature sensor as INPUT
  // start the temperaturesensor

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
  // flash the red LED with digitalWrite()
 
  // If the temperature sensor value is lower then the temperature treshold print "cold" in the serial monitor.
  // flash the blue LED with digitalWrite()

  // create a movement of the servomotor to angle max and min
}