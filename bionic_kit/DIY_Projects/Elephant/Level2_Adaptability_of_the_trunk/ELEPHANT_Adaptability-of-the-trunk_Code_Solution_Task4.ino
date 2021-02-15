// LED
// GPIO
#define LED2 13

// touch sensor
// GPIO
#define touchsensor 16

// lightsensor
// GPIO
#define lightsensor 26
// set treshold for light sensor
#define lightsensor_treshold 3500

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
  //convert 0-180 degrees to 0-65536
  uint32_t conv = (((servomotor_Angle / 180.0) * 2000) / 20000.0 * 65536.0) + 1634;
  ledcWrite(servomotor_Channel, conv);
}

// global variables
char serialprint_buffer[100];

// setup the components.
void setup()
{
  // setup the LED as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup the touch sensor as INPUT
  pinMode(touchsensor, INPUT);

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
  // read and print the current touch sensor value to the serial monitor
  int touchsensor_value = digitalRead(touchsensor);
  sprintf(serialprint_buffer, "touch: %d", touchsensor_value);
  Serial.println(serialprint_buffer);

  // read the current light sensor value
  int lightsensor_value = analogRead(lightsensor);
  sprintf(serialprint_buffer, "light sensor: %d", lightsensor_value);
  Serial.println(serialprint_buffer);

  // day mode: If it's bright enough, print "day" into the serial monitor.
  if (lightsensor_value >= lightsensor_treshold) {
    Serial.println("day");
    // If no touch is detected, move the trunk.
    if (touchsensor_value == LOW) {
      // create a movement of the servomotor to angle max and min
      command_servomotor(servomotor_Angle_Max);
      delay(1000);
      command_servomotor(servomotor_Angle_Min);
      delay(1000);
    }
    //  If a touch is detected, flash the LED.
    else {
      digitalWrite(LED2, HIGH);
      delay(100);
    }
  }
  // night mode: If it's dark engough, print "night" into the serial monitor.
  else {
    Serial.println("night");
  }
  digitalWrite(LED2, LOW);
  delay(100);
}