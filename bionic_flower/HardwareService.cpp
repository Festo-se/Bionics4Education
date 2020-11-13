
// MARK: Includes

#include "HardwareService.h"

// MARK: Constants

const String PRINT_PREFIX = "[HW]: ";
const uint32_t MAX_MEASUREMENT_COUNT = 20;
const float MAX_BRIGHTNESS = 4095;
const float MAX_DISTANCE = 4095;
const float MAX_REOPENCYCLES_LIGHT = 5;
const float MAX_REOPENCYCLES_TOUCH = 5;
const float MAX_REOPENCYCLES_DISTANCE = 5;

// MARK: Variables

HardwareService* shared_instance;

// MARK: Initialization

HardwareService::HardwareService() {
  motor_calibration_finished = false;
  ambient_brightness = DEFAULT_AMBIENT_BRIGHTNESS;
  light_measurement_count = MAX_MEASUREMENT_COUNT;

  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  delay(500);

  Wire.begin(I2C_SDA, I2C_SCL, 100000);
  delay(500);

  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // GPIO Pins

  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);
  pinMode(22, OUTPUT);
  digitalWrite(22, LOW);
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);

  // Input-only Pins

  digitalWrite(34, LOW);
  digitalWrite(35, LOW);

  configuration.motor_position = MOTOR_POSITION_CLOSED; // Flower State
  configuration.lower_brightness_threshold = DEFAULT_LOWER_BRIGHTNESS_THRESHOLD; // Brightness Threshold
  configuration.upper_brightness_threshold = DEFAULT_UPPER_BRIGHTNESS_THRESHOLD; // Brightness Threshold
  configuration.distance_threshold = DEFAULT_DISTANCE_THRESHOLD; // Distance Threshold
  configuration.is_autonomous = DEFAULT_AUTONOMY_VALUE == 1; // Is Autonomy on?
  configuration.color = { 0, 145, 220 };

  sensor_data.has_light_sensor = light_sensor.init() == 0;
  sensor_data.has_touch_sensor = touch_sensor.begin();
  reopen_cycle_count = 0;

  motor.setupPins();
}

// MARK: Static Functions

HardwareService* HardwareService::getSharedInstance() {
  if (shared_instance == nullptr) {
    shared_instance = new HardwareService();
  }
  return shared_instance;
}

// MARK: Methods

boolean HardwareService::start() {
  sensor_timer.detach();

  writeLED({ 0, 255, 0 });
  delay(500);
  writeLED({ 255, 0, 0 });
  delay(500);
  writeLED({ 0, 0, 255 });
  delay(500);
  writeLED(configuration.color);

  Serial.println(PRINT_PREFIX + "Calibrating motor...");

  intended_motor_position = MOTOR_POSITION_OPEN;
  move(MOTOR_POSITION_CLOSED, MOTOR_SPEED_FAST);
  delay((1000 * MOTOR_FULL_STEP_COUNT * MOTOR_SPEED_FAST) + 20);

  while (!motor.isCalibrated()) {
    Serial.println(PRINT_PREFIX + "Still not calibrated.");
    delay(100);
  }

  motor_calibration_finished = true;

  Serial.println(PRINT_PREFIX + "Motor calibration done.");
  return true;
}

void HardwareService::setConfiguration(Configuration new_configuration) {
  Serial.print(PRINT_PREFIX + "New Configuration");
  Serial.print(": Motor Position: " + String(new_configuration.motor_position));
  Serial.print(", Lower Brightness Threshold: " + String(new_configuration.lower_brightness_threshold));
  Serial.print(", Upper Brightness Threshold: " + String(new_configuration.upper_brightness_threshold));
  Serial.print(", Distance Threshold: " + String(new_configuration.distance_threshold));
  Serial.print(", Autonomous: " + String(new_configuration.is_autonomous));
  Serial.print(", Red: " + String(new_configuration.color.red));
  Serial.print(", Green: " + String(new_configuration.color.green));
  Serial.print(", Blue: " + String(new_configuration.color.blue));
  Serial.println();

  boolean control_changed = false;

  if (new_configuration.is_autonomous != configuration.is_autonomous) {
    control_changed = true;
    if (!new_configuration.is_autonomous) {
      motor.stop();
    }
  }

  if ((new_configuration.color.red != configuration.color.red)
      || (new_configuration.color.blue != configuration.color.blue)
      || (new_configuration.color.green != configuration.color.green)) {
    control_changed = true;
  }

  writeLED(new_configuration.color);

  if (((new_configuration.motor_position != configuration.motor_position) || (new_configuration.speed != configuration.speed))
      && (!new_configuration.is_autonomous)
      && (!control_changed)) {

    // The correct way to calculate the speed would be:
    // MOTOR_SPEED_FAST + ((1 - new_configuration.speed) * (MOTOR_SPEED_SLOW - MOTOR_SPEED_FAST));
    // but since Ticker is limited to a time granularity of 0.001, we cannot set any value between 0.001 and 0.002
    float motor_speed = (new_configuration.speed < 0.5) ? MOTOR_SPEED_SLOW : MOTOR_SPEED_FAST;
    move(new_configuration.motor_position, motor_speed);
  }

  this->configuration = new_configuration;
}

void HardwareService::resetSensorData() {
  light_measurement_count = 0;
}

void HardwareService::writeLED(Color color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i].setRGB(color.red, color.green, color.blue);
  }

  FastLED.show();
}

void HardwareService::loop(const boolean has_active_connection, uint32_t loop_counter) {
  if ((loop_counter % 6) == 0) {
    Serial.println(PRINT_PREFIX + "Updating Motor Position.");
    updateMotor();
  } else {
    Serial.println(PRINT_PREFIX + "Reading Sensor Data.");
    readSensors();
  }
}

void HardwareService::readSensors() {

  // update sensor connection status

  if (light_sensor.is_connected() != sensor_data.has_light_sensor) {
    light_sensor = RPR0521RS();
    sensor_data.has_light_sensor = light_sensor.init() == 0;
    Serial.println(PRINT_PREFIX + "Reconnected light sensor? " + (sensor_data.has_light_sensor ? "Success." : "Failed."));
  }

  sensor_data.has_touch_sensor = touch_sensor.isConnected();

  if (!sensor_data.has_touch_sensor) {
    sensor_data.has_touch_sensor = touch_sensor.begin();
    if (sensor_data.has_touch_sensor) {
      Serial.println(PRINT_PREFIX + "Reconnected touch sensor.");
    }
  }

  // update sensor data

  if (sensor_data.has_light_sensor) {
    uint32_t distance;
    float brightness;

    uint8_t rc = light_sensor.get_psalsval(&distance, &brightness);
    if ((distance >= 0) && (brightness >= 0) && (brightness <= MAX_BRIGHTNESS) && (distance <= MAX_DISTANCE) && (rc == 0)) {
      brightness = brightness / MAX_BRIGHTNESS;
      if (light_measurement_count < MAX_MEASUREMENT_COUNT) {
        light_measurement_count++;
        if (light_measurement_count == 1) {
          ambient_brightness = brightness;
        } else {
          ambient_brightness = (0.9 * ambient_brightness) + (0.1 * brightness);
        }
        if (light_measurement_count == MAX_MEASUREMENT_COUNT) {
          configuration.lower_brightness_threshold = max(0.0f, ambient_brightness - DEFAULT_BRIGHTNESS_THRESHOLD_DISTANCE);
          configuration.upper_brightness_threshold = min(1.0f, ambient_brightness + DEFAULT_BRIGHTNESS_THRESHOLD_DISTANCE);
        }
      }

      sensor_data.brightness = brightness;
      sensor_data.distance = 1 - (distance / MAX_DISTANCE);
    }
  }

  if (sensor_data.has_touch_sensor) {
    // They are intentionally flipped, since the existing code recognizes them as the opposite
    sensor_data.touch_left = touch_sensor.isRightTouched();
    sensor_data.touch_right = touch_sensor.isLeftTouched();
  } else {
    sensor_data.touch_left = false;
    sensor_data.touch_right = false;
  }

  // print sensor data

#if DEBUG_AUTONOMOUS_MODE
  Serial.print(PRINT_PREFIX + "Sensor Data ");

  if (sensor_data.has_light_sensor) {
    Serial.print("(brightness: " + String(sensor_data.brightness));
    Serial.print(", ambient: " + String(ambient_brightness));
    Serial.print(", distance: " + String(sensor_data.distance));
    Serial.print(") ");
  }

  if (sensor_data.has_touch_sensor) {
    Serial.print("(touch_left: " + String(sensor_data.touch_left));
    Serial.print(", touch_right: " + String(sensor_data.touch_right));
    Serial.print(") ");
  }

  Serial.println();
  Serial.flush();
#endif
}

void HardwareService::updateMotor() {
  if (!motor_calibration_finished) return;
  if (!configuration.is_autonomous) return;

  configuration.motor_position = 1 - ((float)(motor.getMotorPosition()) / (float)(32 * MOTOR_FULL_STEP_COUNT));
  Serial.println(PRINT_PREFIX + "Updating motor..." + String(light_measurement_count));

  if (sensor_data.has_touch_sensor) {
    if (sensor_data.touch_right) {
      Serial.println(PRINT_PREFIX + "Open due to: Touch right");
      move(MOTOR_POSITION_OPEN, MOTOR_SPEED_FAST);
      reopen_cycle_count = MAX_REOPENCYCLES_TOUCH;
      return;
    } else if (sensor_data.touch_left) {
      Serial.println(PRINT_PREFIX + "Close due to: Touch left");
      move(MOTOR_POSITION_CLOSED, MOTOR_SPEED_FAST);
      reopen_cycle_count = MAX_REOPENCYCLES_TOUCH;
      return;
    }
  }

  if ((sensor_data.has_light_sensor) && (light_measurement_count >= MAX_MEASUREMENT_COUNT)) {
    #if ENABLE_DISTANCE
    if (configuration.distance_threshold > sensor_data.distance) {
      Serial.println(PRINT_PREFIX + "Close due to: Too close");
      move(MOTOR_POSITION_CLOSED, MOTOR_SPEED_FAST);
      reopen_cycle_count = MAX_REOPENCYCLES_DISTANCE;
      return;
    }
    #endif

    if (configuration.lower_brightness_threshold > sensor_data.brightness) {
      Serial.println(PRINT_PREFIX + "Close due to: Too dark");
      move(MOTOR_POSITION_CLOSED, MOTOR_SPEED_FAST);
      reopen_cycle_count = MAX_REOPENCYCLES_LIGHT;
      return;
    } else if (configuration.upper_brightness_threshold < sensor_data.brightness) {
      if (reopen_cycle_count <= 0) {
        Serial.println(PRINT_PREFIX + "Open due to: Too bright");
        move(MOTOR_POSITION_OPEN, MOTOR_SPEED_FAST);
        reopen_cycle_count = 0;
        return;
      } else {
        Serial.println(PRINT_PREFIX + "Could open due to: Too bright");
        reopen_cycle_count--;
      }
    }
  }

  motor.stop();
}

// position: 1.0f (open), 0.0f (close)
// speed: Use MOTOR_SPEED_SLOW or MOTOR_SPEED_FAST
void HardwareService::move(float position, float speed) {
  Serial.println(PRINT_PREFIX + "move(" + String(position) + ", " + String(speed * 100) + ")");
  if (abs(intended_motor_position - position) < 0.005) {
    motor.rotate(speed);
    return;
  }

  intended_motor_position = position;

  if (motor.isOpening() || motor.isClosing()) {
    motor.stop();
  }

  int32_t steps = position * MOTOR_FULL_STEP_COUNT - (((float)motor.getMotorPosition()) / 32);
  if (abs(steps) < 1) return;

  Serial.println(PRINT_PREFIX + "Current Motor Position: " + String(motor.getMotorPosition() / 32));
  Serial.println(PRINT_PREFIX + "Position: " + String(position));
  Serial.println(PRINT_PREFIX + "Intended Motor Position: " + String(position * MOTOR_FULL_STEP_COUNT));
  Serial.println(PRINT_PREFIX + "Move to " + String(position) + " with speed " + String(speed) + ", steps: " + steps);

  motor.setMotorCurrent(MOTOR_CURRENT_LOW);
  motor.setDirection(steps > 0 ? MotorLogic::OPEN : MotorLogic::CLOSE);
  motor.setNSteps(abs(steps));
  motor.setSteppingMode(MotorLogic::M1);
  motor.wakeup();
  motor.rotate(speed);
}
