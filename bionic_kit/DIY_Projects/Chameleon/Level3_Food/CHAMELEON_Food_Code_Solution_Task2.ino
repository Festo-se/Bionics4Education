// LED2 (built-in ESP32)
// GPIO
#define LED2 13

// LED_RGB_Green
// GPIO green color
#define LED_RGB_Green 16

// touch sensor
// GPIO

// vibrating motor
// GPIO

// servomotor
// library
// GPIO
// PWM properties servomotor
// define servomotor angles
// command_servomotor(): give the angle to the function command_servomotor() and move to the servomotor to the servomotor_Angle
//convert 0-180 degrees to 0-65536

// global variables

// setup the components
void setup()
{
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup LED_RGB_Green as OUTPUT
  pinMode(LED_RGB_Green, OUTPUT);

  // setup the touch sensor as INPUT

  // setup vibrating motor

  // setup servomotor as OUTPUT
  // attach the channel to the GPIO to be controlled
  // define the PWM functionalities of the channel

  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED2, HIGH);
  digitalWrite(LED_RGB_Green, LOW);
  delay(1000);
  digitalWrite(LED2, LOW);
  digitalWrite(LED_RGB_Green, HIGH);
  delay(1000);
  // read and print the current touch sensor value to the serial monitor

  // If a touch is detected, the food game begins.
  // generate a random value between 0 and 1
  // print the random value into the serial monitor

  // If the random value is eqaual to 1, the player "wins". Change the color of the chameleon to green and start the tongue movement.
  // If the random value is not eqaual to 1, the player "lose". Change the color of the chameleon to red and start the vibrating motor.
  // If no touch is detected, the game stops. Set the parametes of LED2, LED_RGB_Grenn and vibrating motor to LOW. Print the information "no touch detected" into the serial monitor.
}