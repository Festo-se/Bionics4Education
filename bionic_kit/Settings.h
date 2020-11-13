
#ifndef SETTINGS_H_
#define SETTINGS_H_

// SERVO SETTINGS

const uint8_t GPIO_SERVO_0 = 25;
const uint8_t GPIO_SERVO_1 = 26;
const uint8_t GPIO_SERVO_2 = 17;
const uint8_t GPIO_SERVO_3 = 16;

// PPM SERVO SETTINGS

const int16_t MIN_PPM_VALUE = 800;
const int16_t MAX_PPM_VALUE = 2400;

// BIONIC FISH SETTINGS

// FISH_POSITION_LEFT, FISH_POSITION_CENTER and FISH_POSITION_RIGHT describe three important positions of the servo motor
// FISH_POSITION_LEFT is the position in which the left side of the stick is touching the fish body
// FISH_POSITION_CENTER is the the position in which the stick is horizontal
// FISH_POSITION_RIGHT is the position in which the right side of the stick is touching the fish body
//
// Examples:
// - Water-Proof Servo
//     LEFT: 20, CENTER: 72, RIGHT: 124
// - Normal Servo
//     LEFT: 30, CENTER: 80, RIGHT: 130
// 
const int16_t FISH_POSITION_LEFT = 20;
const int16_t FISH_POSITION_CENTER = 72;
const int16_t FISH_POSITION_RIGHT = 124;

const float FISH_FREQUENCY_MIN = 10.0f;
const float FISH_FREQUENCY_MAX = 25.0f;
const float FISH_FREQUENCY_DEFAULT = 20.0f;

const int16_t FISH_STEP_MIN = 2;
const int16_t FISH_STEP_MAX = 7;
const int16_t FISH_STEP_DEFAULT = 5;

const int16_t FISH_AMPLITUDE_MIN = 60; // Suggestion: 20
const int16_t FISH_AMPLITUDE_MAX = 110; // Suggestion: 70

const int16_t FISH_OFFSET_MAX = 30; // Suggestion: 15

// FISH_FREQUENCY_MODE controls whether to modify the speed by changing the frequency or the step size.
// - true --> frequency is set to value between FISH_FREQUENCY_MIN and FISH_FREQUENCY_MAX, step size is FISH_STEP_DEFAULT.
// - false --> frequency is set to FISH_FREQUENCY_DEFAULT, step size is set to value between FISH_STEP_MIN and FISH_STEP_MAX.
const boolean FISH_FREQUENCY_MODE = false;

// FISH_AMPLITUDE_OVERDRAFT is an option that allows for a value to go beyond FISH_POSITION_LEFT and FISH_POSITION_RIGHT.
// If set to false, it ensures that the amplitude of the fish movement stays inside FISH_POSITION_LEFT and FISH_POSITION_RIGHT.
const boolean FISH_AMPLITUDE_OVERDRAFT = true; // Suggestion: false

#endif
