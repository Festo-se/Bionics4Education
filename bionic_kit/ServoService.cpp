
// MARK: Includes

#include "ServoService.h"
#include "Helpers.h"

// MARK: Defines

#define LED_BUILTIN 13

// MARK: Constants

const String PRINT_PREFIX = "[SERVO]: ";
const int32_t LED_LOOP_COUNTER_LENGTH = 200000;

// MARK: Variables

ServoService* shared_instance;

// MARK: Initialization

ServoService::ServoService() {
  servo_0 = new Servo();
  servo_1 = new Servo();
  servo_2 = new Servo();
  servo_3 = new Servo();

  led_loop_counter = 0;
  led_is_on = false;
  led_loop_counter_length = LED_LOOP_COUNTER_LENGTH;
  led_is_blinking = false;

  pinMode(LED_BUILTIN, OUTPUT);
  writeLED(led_is_on);

  project = chameleon;
  setProject(fish);
}

// MARK: Static Functions

ServoService* ServoService::getSharedInstance() {
  if (shared_instance == nullptr) {
    shared_instance = new ServoService();
  }
  return shared_instance;
}

// MARK: Methods

void ServoService::setProject(Project project) {
  if (project == this->project) {
    return;
  }
  this->project = project;

  fish_timer.detach();
  detachAll();

  SliderConfiguration new_configuration = SliderConfiguration();
  switch (project) {
    case fish:
      Serial.println(PRINT_PREFIX + "Switching to FISH.");
      new_configuration.slider_value_0 = 0;
      new_configuration.slider_value_1 = 0;
      new_configuration.slider_value_2 = 50;
      new_configuration.slider_value_3 = 0;
      break;
    case elephant:
      Serial.println(PRINT_PREFIX + "Switching to ELEPHANT.");
      new_configuration.slider_value_0 = 30;
      new_configuration.slider_value_1 = 30;
      new_configuration.slider_value_2 = 30;
      new_configuration.slider_value_3 = 30;
      break;
    case chameleon:
      Serial.println(PRINT_PREFIX + "Switching to CHAMELEON.");
      new_configuration.slider_value_0 = 90;
      new_configuration.slider_value_1 = 90;
      new_configuration.slider_value_2 = 90;
      new_configuration.slider_value_3 = 90;
      break;
  }

  setConfiguration(new_configuration);
}

void ServoService::setConfiguration(SliderConfiguration new_configuration) {
  Serial.print(PRINT_PREFIX + "Sliders");
  Serial.print(": " + String(new_configuration.slider_value_0));
  Serial.print(", " + String(new_configuration.slider_value_1));
  Serial.print(", " + String(new_configuration.slider_value_2));
  Serial.print(", " + String(new_configuration.slider_value_3));
  Serial.println();
  led_is_blinking = true;

  switch (project) {
    case chameleon:
      writeServos(new_configuration);
      break;
    case elephant:
      writeServos(new_configuration);
      break;
    case fish:
      resetFishTimer(new_configuration);
      break;
  }

  this->configuration = new_configuration;
}

void ServoService::update(const boolean has_active_connection) {

  if (!has_active_connection) {
    writeLED(true);
  } else {
    if (led_is_blinking) {
      if (led_loop_counter < led_loop_counter_length) {
        writeLED(true);
      } else {
        writeLED(false);
        led_loop_counter = 0;
        led_is_blinking = false;
      }
      led_loop_counter++;
    } else {
      writeLED(false);
    }
  }

}

void ServoService::fishLoop() {
  if (servo_speed < 0.1f) return;

  // Add servo_add_value to the last position value
  servo_position += servo_step;

  // If the position gets larger than the max. amplitude, switch the direction
  if (servo_position > servo_amplitude_max) {
    servo_position = servo_amplitude_max;
    servo_step *= -1;
  }

  // If the position gets smaller than the min. amplitude, switch the direction
  if (servo_position < servo_amplitude_min) {
    servo_position = servo_amplitude_min;
    servo_step *= -1;
  }

  Serial.println(PRINT_PREFIX + "Position: " + String(servo_position) + ", min: " + String(servo_amplitude_min) + ", max: " + String(servo_amplitude_max));

  writeServos(configuration);
}

// MARK: Helpers

void ServoService::writeLED(boolean is_on) {
  if (is_on != led_is_on) {
    led_is_on = is_on;
    digitalWrite(LED_BUILTIN, is_on ? HIGH : LOW);
  }
}

void ServoService::write(Servo* servo, int16_t value) {
  int8_t index = 4;
  if (servo == servo_0) {
    index = 0;
    if (servo_0_value == value) {
      return;
    }

    servo_0_value = value;
  } else if (servo == servo_1) {
    index = 1;
    if (servo_1_value == value) {
      return;
    }
    servo_1_value = value;
  } else if (servo == servo_2) {
    index = 2;
    if (servo_2_value == value) {
      return;
    }
    servo_2_value = value;
  } else if (servo == servo_3) {
    index = 3;
    if (servo_3_value == value) {
      return;
    }
    servo_3_value = value;
  } else {
    Serial.println(PRINT_PREFIX + "Writing " + String(value) + " to unknown servo.");
    return;
  }

  attachIfNeeded(servo);
  servo->write(value);
}

void ServoService::resetFishTimer(SliderConfiguration new_configuration) {
  fish_timer.detach();

  // Slider 1: Transforming slider value from range [0, 100] to [0, 1]
  servo_speed = new_configuration.slider_value_0 / 100.0f;

  // If speed is smaller than 0.1f, there should be no movement
  if (servo_speed <= 0.1f) return;

  // Slider 2: Transforming slider value from range [-100, 100] to [-1, 1]
  float offset_multiplier = new_configuration.slider_value_1 / 100.0f;

  // Slider 3: Transforming slider value from range [0, 100] to [0, 1]
  float amplitude_multiplier = new_configuration.slider_value_2 / 100.0f;

  if (FISH_FREQUENCY_MODE) {
    servo_step = FISH_STEP_DEFAULT;
  } else {
    servo_step = FISH_STEP_MIN + (servo_speed * (FISH_STEP_MAX - FISH_STEP_MIN));
  }

  // servo_offset is the position at the center of the movement
  int16_t servo_offset = FISH_POSITION_CENTER + (offset_multiplier * FISH_OFFSET_MAX);

  // servo_amplitude_min is the left-most position of the movement
  // servo_amplitude_max is the right-most position of the movement
  // half_amplitude is the distance between servo_offset and the min and max values of the movement
  int16_t amplitude = (amplitude_multiplier * (FISH_AMPLITUDE_MAX - FISH_AMPLITUDE_MIN)) + FISH_AMPLITUDE_MIN;
  servo_amplitude_min = servo_offset - (amplitude / 2);
  servo_amplitude_max = servo_offset + (amplitude / 2);

  if (!FISH_AMPLITUDE_OVERDRAFT) {
    servo_amplitude_min = max(FISH_POSITION_LEFT, servo_amplitude_min);
    servo_amplitude_max = min(FISH_POSITION_RIGHT, servo_amplitude_max);
  }

  Serial.print(PRINT_PREFIX + "Fish Movement Changed");
  Serial.print(" - Speed: " + String(servo_speed));
  Serial.print(" - Offset: " + String(servo_offset));
  Serial.print(" - Amplitude: " + String(servo_amplitude_min) + " to " + String(servo_amplitude_max));
  Serial.println();

  float duration;
  if (FISH_FREQUENCY_MODE) {
    duration = 1.0f / (FISH_FREQUENCY_MIN + (servo_speed * (FISH_FREQUENCY_MAX - FISH_FREQUENCY_MIN)));
  } else {
    duration = 1.0f / FISH_FREQUENCY_DEFAULT;
  }

  fish_timer.attach(duration, &globalFishLoop);
}

void ServoService::attachIfNeeded(Servo* servo) {
  if (servo == servo_0) {
    servo->attach(GPIO_SERVO_0, MIN_PPM_VALUE, MAX_PPM_VALUE);
    Serial.println(PRINT_PREFIX + "Attached servo 0.");
  } else if (servo == servo_1) {
    servo->attach(GPIO_SERVO_1, MIN_PPM_VALUE, MAX_PPM_VALUE);
    Serial.println(PRINT_PREFIX + "Attached servo 1.");
  } else if (servo == servo_2) {
    servo->attach(GPIO_SERVO_2, MIN_PPM_VALUE, MAX_PPM_VALUE);
    Serial.println(PRINT_PREFIX + "Attached servo 2.");
  } else if (servo == servo_3) {
    servo->attach(GPIO_SERVO_3, MIN_PPM_VALUE, MAX_PPM_VALUE);
    Serial.println(PRINT_PREFIX + "Attached servo 3.");
  } else {
    Serial.println(PRINT_PREFIX + "Trying to attach invalid servo.");
  }
}

void ServoService::detachAll() {
  servo_0->detach();
  servo_1->detach();
  servo_2->detach();
  servo_3->detach();
  Serial.println(PRINT_PREFIX + "Detached all servos.");
}

void ServoService::writeServos(SliderConfiguration new_configuration) {
  switch (project) {
    case chameleon:
      write(servo_0, new_configuration.slider_value_0);
      write(servo_1, new_configuration.slider_value_1);
      write(servo_2, new_configuration.slider_value_2);
      write(servo_3, new_configuration.slider_value_3);
      break;
    case elephant:
      detachAll();
      write(servo_0, new_configuration.slider_value_0);
      write(servo_1, new_configuration.slider_value_1);
      write(servo_2, new_configuration.slider_value_2);
      write(servo_3, new_configuration.slider_value_3);
      break;
    case fish:
      write(servo_0, servo_position);
      write(servo_1, servo_position);
      write(servo_2, servo_position);
      write(servo_3, servo_position);
      break;
  }
}
