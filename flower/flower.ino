
// MARK: Includes

#include "Models.h"
#include "WebService.h"
#include <exception>
#include <esp_task_wdt.h>
// MARK: Constants

const String VERSION =  "v1.4";
const String DATE = __DATE__;
const String TIME = __TIME__;
const String PRINT_PREFIX = "[SKETCH]: ";

const IPAddress IP_ADDRESS = IPAddress(192, 168, 4, 1);
const uint16_t PORT = 80;

const long BAUD_RATE = 115200;
const unsigned long MIN_LOOP_DURATION = 100;

uint32_t loop_count = 0;
boolean has_started = false;

// MARK: Variables

WebService* web_service;

// MARK: Methods

void setup() {
  Serial.begin(BAUD_RATE);

  while (!Serial);

  esp_task_wdt_init(60, false);

  Serial.println(PRINT_PREFIX + "Version: " + VERSION);
  Serial.println(PRINT_PREFIX + "Build Date: " + DATE);
  Serial.println(PRINT_PREFIX + "Build Time: " + TIME);

  web_service = new WebService();
  web_service->start(IP_ADDRESS, PORT, [](boolean success) {
    Serial.println(PRINT_PREFIX + (success ? "Success" : "Failed"));
    has_started = true;
  });
}

void loop() {
  try {
    loop_count++;
    Serial.println(PRINT_PREFIX + "Loop " + String(loop_count));
    unsigned long start_time = millis();
    web_service->loop(loop_count);
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
