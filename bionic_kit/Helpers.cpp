
// MARK: Includes

#include "Helpers.h"

// MARK: Methods

void globalFishLoop() {
  ServoService* servo_service = ServoService::getSharedInstance();
  servo_service->fishLoop();
}
