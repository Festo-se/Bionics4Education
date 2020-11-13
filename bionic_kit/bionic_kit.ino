
// MARK: Includes

#include "Models.h"
#include "WebService.h"
#include <exception>

// MARK: Constants

const String PRINT_PREFIX = "[SKETCH]: ";
const String VERSION =  "v1.4";
const String DATE =  __DATE__;
const String TIME = __TIME__;

const IPAddress IP_ADDRESS = IPAddress(192, 168, 4, 1);
const uint16_t PORT = 80;

const unsigned long MIN_LOOP_DURATION = 100;

const long BAUD_RATE = 115200;

// MARK: Variables

WebService* web_service;

// MARK: Methods

void setup() {
  Serial.begin(BAUD_RATE);

  while (!Serial);

  Serial.println(PRINT_PREFIX + "Version: " + VERSION);
  Serial.println(PRINT_PREFIX + "Build Date: " + DATE);
  Serial.println(PRINT_PREFIX + "Build Time: " + TIME);

  web_service = new WebService();
  web_service->start(IP_ADDRESS, PORT, [](boolean success) {
    Serial.println(PRINT_PREFIX + (success ? "Success" : "Failed"));
  });
}

void loop() {
  try {
    unsigned long start_time = millis();
    web_service->loop();
    unsigned long end_time = millis();
    if (end_time > start_time) { // millis has the possibility to overflow every 50 days.
      long delay_duration = ((long)start_time - (long)end_time) + (long)MIN_LOOP_DURATION;
      delay((delay_duration >= 0) ? delay_duration : 0);
    }
  } catch (const std::runtime_error& error) {
    Serial.println(PRINT_PREFIX + "Loop caused error: " + error.what() + ".");
  } catch (const std::exception& exception) {
    Serial.println(PRINT_PREFIX + "Loop caused exception: " + exception.what() + ".");
  } catch (...) {
    Serial.println(PRINT_PREFIX + "Loop caused unknown failure.");
  }
}
