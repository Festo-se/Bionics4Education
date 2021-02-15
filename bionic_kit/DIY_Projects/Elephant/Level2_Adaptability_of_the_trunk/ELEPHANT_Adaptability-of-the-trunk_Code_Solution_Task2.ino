// LED
// GPIO
#define LED2 13

// touch sensor
// GPIO
#define touchsensor 16

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
char serialprint_buffer[100];

//Setup the components.
void setup()
{
  // setup the LED as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup the touch sensor as INPUT
  pinMode(touchsensor, INPUT);

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
  int touchsensor_value = digitalRead(touchsensor);
  sprintf(serialprint_buffer, "touch: %d", touchsensor_value);
  Serial.println(serialprint_buffer);

  // read the current light sensor value

  // day mode: If it's bright enough, print "day" into the serial monitor.
  // If no touch is detected, move the trunk.
  if (touchsensor_value == LOW) {
    // create a movement of the servomotor to angle max and min

  }
  //  If a touch is detected, flash the LED.
  else {
    digitalWrite(LED2, HIGH);
    delay(100);
  }

  // night mode: If it's dark engough, print "night" into the serial monitor.

  digitalWrite(LED2, LOW);
  delay(100);
}