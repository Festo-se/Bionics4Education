// LED
// GPIO
#define LED_RGB_Green 16

// light sensor
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

// setup the components
void setup()
{
  // setup LED as OUTPUT
  pinMode (LED_RGB_Green, OUTPUT);

  // setup the light sensor as INPUT

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  Serial.begin(9600);
  // setup the serial communication
}

void loop()
{
  // read the current light sensor value

  // If the light sensor value is equal of higher then the light treshold start the game.
  // generate a random value between 0 and 1
  // print the random value into the serial monitor

  // If the random value is eqaual to 1, the player "wins". Change the color of the fish to green and start the finray movement.
  // print "win" into the serial monitor
  // power on the green LED
  digitalWrite(LED_RGB_Green, HIGH);
  // power off the red LED
  // create a movement of the servomotor to angle max and min
  delay(1000);

  // If the random value is not eqaual to 1, the player "lose". Change the color of the fish to red and write "lose" into the serial monitor.

  // If the light sensor value is lower then the light treshold print "lose" in the serial monitor.
  // power off the green LED
  digitalWrite(LED_RGB_Green, LOW);
  // power on the red LED
  delay(1000);

  // power off the green and red LED
}