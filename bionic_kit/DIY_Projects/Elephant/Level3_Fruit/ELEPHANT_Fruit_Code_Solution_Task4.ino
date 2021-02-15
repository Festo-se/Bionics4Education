// LED2 (built-in ESP32)
// GPIO
#define LED2 13

// touch sensor
// GPIO
#define touchsensor 16

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
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup the touch sensor as INPUT
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
  // read and print the current touch sensor value to the serial monitor
  int touchsensor_value = digitalRead(touchsensor);
  sprintf(serialprint_buffer, "touch: %d", touchsensor_value);
  Serial.println(serialprint_buffer);

  // If a touch is detected the game starts.
  if (touchsensor_value == HIGH) {
    // print "touch detected" into the serial monitor.
    Serial.println("touch detected");
    // generate a random value between 0 and 1
    int random_value = random(2);
    // print the random value into the serial monitor
    sprintf(serialprint_buffer, "random value: %d", random_value);
    Serial.println(serialprint_buffer);

    // If the random value is eqaual to 1, the player "wins".
    if (random_value == 1) {
      // print "win" into the serial monitor.
      Serial.println("win");
      // create a movement of the servomotor to angle max and min
      command_servomotor(servomotor_Angle_Max);
      delay(1000);
      command_servomotor(servomotor_Angle_Min);
      delay(1000);
    }

    // If the random value is not equal to 1, the player "lose".
    else {
      // print "win" into the serial monitor.
      Serial.println("lose");
      // flash the LED
      digitalWrite(LED2, HIGH);
      delay(500);
      digitalWrite(LED2, LOW);
      delay(500);
    }
  }
  else {
    // print "no touch detected" into the serial monitor.
    Serial.println("no touch detected");
    delay(1000);
  }
}