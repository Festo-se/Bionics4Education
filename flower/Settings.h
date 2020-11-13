
#ifndef SETTINGS_H_
#define SETTINGS_H_

#define MOTOR_FULL_STEP_COUNT 14000 // number of motor steps for full up/down (festo variant)
#define MOTOR_CURRENT_LOW 250
#define DEFAULT_LOWER_BRIGHTNESS_THRESHOLD 0.2f // default brightness threshold
#define DEFAULT_UPPER_BRIGHTNESS_THRESHOLD 0.4f // default brightness threshold
#define DEFAULT_AMBIENT_BRIGHTNESS 0.3f
#define DEFAULT_BRIGHTNESS_THRESHOLD_DISTANCE 0.1f
#define DEFAULT_DISTANCE_THRESHOLD 0.6f // default ADC touch threshold
#define DEFAULT_AUTONOMY_VALUE 0
#define MOTOR_SPEED_SLOW 0.002f
#define MOTOR_SPEED_FAST 0.001f

#define LED_COUNT 5
#define LED_PIN 16

#define I2C_SDA 4
#define I2C_SCL 5

#define PIN_IR_LED 4

#define DEBUG_AUTONOMOUS_MODE true
#define DEBUG_MANUAL_MODE true

#define MOTOR_POSITION_OPEN 1.0f
#define MOTOR_POSITION_CLOSED 0.0f

#endif
