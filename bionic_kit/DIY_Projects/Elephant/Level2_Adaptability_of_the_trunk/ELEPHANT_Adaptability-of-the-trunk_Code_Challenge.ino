// LED
// GPIO

// touch sensor
// GPIO

// lightsensor
// GPIO
// set treshold for light sensor

// servomotor
// library
// GPIO
// PWM properties servomotor
// define servomotor angles

// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle
// convert 0-180 degrees to 0-65536

// global variables

//Setup the components.
void setup()
{
  // setup the LED as OUTPUT

  // setup the touch sensor as INPUT

  // setup the light sensor as INPUT

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // read and print the current touch sensor value to the serial monitor

  // read the current light sensor value

  // day mode: If it's bright enough, print "day" into the serial monitor.
  // If no touch is detected, move the trunk.
  // create a movement of the servomotor to angle max and min

  //  If a touch is detected, flash the LED.

  // night mode: If it's dark engough, print "night" into the serial monitor.
}