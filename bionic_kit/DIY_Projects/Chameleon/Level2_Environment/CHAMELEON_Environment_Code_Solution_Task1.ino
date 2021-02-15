// LED2
// GPIO
#define LED2 13

// GPIO of RGB LED and vibration motor
// PWM properties RGB LED
// global variables RGB LED

// lightsensor
// GPIO
// set treshold for light sensor

// touch sensor
// GPIO

// servomotor
// library
// GPIO
// PWM properties servomotor
// define servomotor angles
// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle

// global variables

// setup the components
void setup()
{
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup LED_RGB as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the light sensor as INPUT

  // setup touch sensor

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // read the current light sensor value and print it in the serial monitor.
  // If the light sensor value is equal of higher then the light treshold print "day" in the serial monitor.
  // read and print the current touch sensor value to the serial monitor
  // If the touch sensor detect a signal, flash the red LED and write "danger" in the serial monitor.
      digitalWrite(LED2, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
 
  // If the touch sensor detect no signal, move the servomotor (tounge).
  // create a movement of the servomotor to angle max and min

  // If the light sensor value is lower then the light treshold print "night" in the serial monitor. And fade the vibrating motor and RGB LED.
  // Wait for 100 milliseconds to see the dimming effect of the LED.

  // Change the current_value for next run of the loop.

  // Reverse the direction of the fading at the ends of a fading cycle.
}