
#ifndef MODELS_H_
#define MODELS_H_

// MARK: Includes

#include <SPIFFS.h>
#include <string>

// MARK: Types

struct Color {
  uint8_t red; // Red Value [0, 255]
  uint8_t green; // Green Value [0, 255]
  uint8_t blue; // Blue Value [0, 255]

  boolean operator==(Color other) const {
    return (red == other.red) &&
           (green == other.green) &&
           (blue == other.blue);
  }

  boolean operator!=(Color other) const {
    return !(*this == other);
  }

  String hexString() {
    return "#" + hexComponent(red) + hexComponent(green) + hexComponent(blue);
  }

  String hexComponent(uint8_t value) {
    String string = String(value, HEX);
    return (string.length() < 2) ? ("0" + string) : string;
  }

  static Color fromHexString(String hex) {
    hex.replace(" ", "");
    hex.replace("#", "");
    int number;
    switch (hex.length()) {
      case 6:
        number = (int)strtol(hex.c_str(), NULL, 16);
        return {
          (uint8_t)((number >> 16) & 0xFF),
          (uint8_t)((number >>  8) & 0xFF),
          (uint8_t)((number >>  0) & 0xFF),
        };
      case 8:
        number = (int)strtol(hex.c_str(), NULL, 16);
        return {
          (uint8_t)((number >> 24) & 0xFF),
          (uint8_t)((number >> 16) & 0xFF),
          (uint8_t)((number >>  8) & 0xFF),
        };
      default:
        Serial.println("[COLOR]: Invalid hex string could not result in color value: \"" + hex + "\".");
        return {};
    }
  }
};

struct Configuration {
  float motor_position; // Motor Position [0 (closed), 1 (open)]
  float upper_brightness_threshold; // Brightness Threshold [0, 1]
  float lower_brightness_threshold; // Brightness Threshold [0, 1]
  float distance_threshold; // Distance Threshold [0, 1]
  float speed;
  boolean is_autonomous; // Is Autonomy on?
  Color color;
};

struct SensorData {

  boolean has_light_sensor;
  float brightness; // Ambient Light Sensor Value [0 (dark), 1 (bright)]
  float distance; // Proximity Sensor Value [0 (close), 1 (far)]

  boolean has_touch_sensor;
  boolean touch_left; // Touch Pad Left is tapped
  boolean touch_right; // Touch Pad Right is tapped

};

#endif
