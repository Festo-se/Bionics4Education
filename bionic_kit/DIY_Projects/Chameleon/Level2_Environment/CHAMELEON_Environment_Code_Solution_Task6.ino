// LED2
// GPIO
#define LED2 13

// GPIO of RGB LED and vibration motor
#define LED_RGB 16
// PWM properties RGB LED
int LED_RGB_Channel = 12;
int LED_RGB_Channel_Frequency = 5000;
int LED_RGB_Channel_Resolution = 8;
// global variables RGB LED
int LED_RGB_brightness_high = 255;
int LED_RGB_brightness_low = 0;

// lightsensor
// GPIO
#define lightsensor 26
// set treshold for light sensor
int lightTreshold = 3500;

// touch sensor
// GPIO
#define touchsensor 17

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
int current_value = 0;
int stepSize = 8;
char serialprint_buffer[100];

// setup the components
void setup()
{
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup LED_RGB as OUTPUT
  pinMode(LED_RGB, OUTPUT);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_RGB, LED_RGB_Channel);
  // define the PWM functionalities of the channel
  ledcSetup(LED_RGB_Channel, LED_RGB_Channel_Frequency, LED_RGB_Channel_Resolution);

  // setup the light sensor as INPUT
  pinMode(lightsensor, INPUT);

  //  setup touch sensor
  pinMode(touchsensor, INPUT);

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
  // read the current light sensor value and print it in the serial monitor.
  int lightsensor_value = analogRead(lightsensor);
  sprintf(serialprint_buffer, "Light sensor value: %d", lightsensor_value);
  Serial.println(serialprint_buffer);

  // If the light sensor value is equal of higher then the light treshold print "day" in the serial monitor.
  if (lightsensor_value >= lightTreshold) {
    Serial.println("day");
    ledcWrite(LED_RGB_Channel, 0);
    // read and print the current touch sensor value to the serial monitor
    int touchsensor_value = digitalRead(touchsensor);
    sprintf(serialprint_buffer, "touch: %d", touchsensor_value);
    Serial.println(serialprint_buffer);

    // If the touch sensor detect a signal, flash the red LED and write "danger" in the serial monitor.
    if (touchsensor_value == HIGH) {
      digitalWrite(LED2, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
      Serial.println("danger");
    }

    // If the touch sensor detect no signal, move the servomotor (tounge).
    else {
      Serial.println("no touch detected");
      // create a movement of the servomotor to angle max and min
      command_servomotor(servomotor_Angle_Max);
      delay(1000);
      command_servomotor(servomotor_Angle_Min);
      delay(1000);
    }
  }

  // If the light sensor value is lower then the light treshold print "night" in the serial monitor. And fade the vibrating motor and RGB LED.
  else {
    digitalWrite(LED2, LOW);
    ledcWrite(LED_RGB_Channel, current_value);
    // Wait for 100 milliseconds to see the dimming effect of the LED.
    delay(100);
    Serial.println("night");
  }

  // Change the current_value for next run of the loop.
  current_value = current_value + stepSize;

  // Reverse the direction of the fading at the ends of a fading cycle.
  if (current_value <= LED_RGB_brightness_low || current_value >= LED_RGB_brightness_high) {
    stepSize = -stepSize;
  }
}