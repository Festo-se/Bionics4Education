// ----- SERVO SETTINGS ----- //
const uint8_t GPIO_SERVO_01 = 25;
const uint8_t GPIO_SERVO_02 = 26;
const uint8_t GPIO_SERVO_03 = 17;
const uint8_t GPIO_SERVO_04 = 16;

//PPM Settings for Servo
const int16_t MIN_PPM_VALUE = 800;
const int16_t MAX_PPM_VALUE = 2400;

// ----- BIONIC FISH SETTINGS ----- //

const int16_t FISH_AMPLITUDE_CENTER_DEFAULT = 80;
const float FISH_AMPLITUDE_MULTIPLIER = 1.0;

//Update Frequency for Servo in Hz
//If frequency is to low, the servo runns not smooth anymore
//If the frequency is to high, the servo gets overwritten and the serial connection crashes!!!
//Maybe a problem with the write time to the servo. 
const float MIN_SERVO_UPDATE_FREQ = 10.0;
const float MAX_SERVO_UPDATE_FREQ = 25.0;
