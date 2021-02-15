// LED2 (built-in ESP32)
// GPIO

// touch sensor
// GPIO

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
  // setup LED2 as OUTPUT

  // setup the touch sensor as INPUT

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // read and print the current touch sensor value to the serial monitor

  // If a touch is detected the game starts.
  // print "touch detected" into the serial monitor.
  // generate a random value between 0 and 1
  // print the random value into the serial monitor

  // If the random value is eqaual to 1, the player "wins".
  // print "win" into the serial monitor.
  // create a movement of the servomotor to angle max and min

  // If the random value is not equal to 1, the player "lose".
  // print "win" into the serial monitor.
  // flash the LED

  // print "no touch detected" into the serial monitor.
}