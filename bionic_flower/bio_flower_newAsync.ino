
// MARK: Includes

#include "Models.h"
#include "WebService.h"
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
uint32_t lastLoopMs = 0;

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
    has_started = true;
  });
}

void loop() {
    uint32_t timeDeltaMs = millis() - lastLoopMs;
    if(timeDeltaMs >= MIN_LOOP_DURATION){
      loop_count++;
#if DEBUG_MANUAL_MODE || DEBUG_AUTONOMOUS_MODE
    Serial.println(PRINT_PREFIX + "Loop " + String(loop_count));
#endif
      web_service->loop(loop_count);
      lastLoopMs = millis();
    }
}
