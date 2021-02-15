// LED
// GPIO
#define LED_RGB_Green 16
#define LED_RGB_Red 17

// light sensor
// GPIO
#define lightsensor 26
// set treshold for light sensor
int lightTreshold = 2500;

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
  // setup LED as OUTPUT
  pinMode (LED_RGB_Green, OUTPUT);
  pinMode (LED_RGB_Red, OUTPUT);

  // setup the light sensor as INPUT
  pinMode(lightsensor, INPUT);

  // setup servomotor as OUTPUT
  pinMode(servomotor, OUTPUT);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(servomotor, servomotor_Channel);
  // define the PWM functionalities of the channel
  ledcSetup(servomotor_Channel, servomotor_Frequency, servomotor_Resolution);

  Serial.begin(9600);
  // setup the serial communication
}

void loop()
{
  // read the current light sensor value
  int lightsensor_value = analogRead(lightsensor);
  sprintf(serialprint_buffer, "Light sensor value: %d", lightsensor_value);
  Serial.println(serialprint_buffer);

  // If the light sensor value is equal of higher then the light treshold start the game.
  if (lightsensor_value >= lightTreshold) {
    // generate a random value between 0 and 1
    int random_value = random(2);
    // print the random value into the serial monitor
    sprintf(serialprint_buffer, "game starts -> random value: %d", random_value);
    Serial.println(serialprint_buffer);

    // If the random value is eqaual to 1, the player "wins". Change the color of the fish to green and start the finray movement.
    if (random_value == 1) {
      // print "win" into the serial monitor
      Serial.println("win");
      // power on the green LED
      digitalWrite(LED_RGB_Green, HIGH);
      // power off the red LED
      digitalWrite(LED_RGB_Red, LOW);
      // create a movement of the servomotor to angle max and min
      command_servomotor(servomotor_Angle_Max);
      delay(1000);
      command_servomotor(servomotor_Angle_Min);
      delay(1000);
    }
    // If the random value is not eqaual to 1, the player "lose". Change the color of the fish to red and write "lose" into the serial monitor.
    else {
      // If the light sensor value is lower then the light treshold print "lose" in the serial monitor.
      Serial.println("lose");
      // power off the green LED
      digitalWrite(LED_RGB_Green, LOW);
      // power on the red LED
      digitalWrite(LED_RGB_Red, HIGH);
      delay(1000);
    }
  }
  else {
    // power off the green and red LED
    digitalWrite(LED_RGB_Green, LOW);
    digitalWrite(LED_RGB_Red, LOW);
    delay(1000);
  }
}