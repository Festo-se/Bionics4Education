
#ifndef WIFISERVICE_H_
#define WIFISERVICE_H_

// MARK: Includes

#include <WiFi.h>
#include "Models.h"

class WiFiService {

  public:

    // MARK: Initialization

    WiFiService();

    // MARK: Methods

    void start(IPAddress ip, std::function<void(bool)> completion);
    int getActiveConnectionCount();

  protected:

  private:

    // MARK: Private Properties

    IPAddress ip_address;
    std::function<void(bool)> start_completion;

    // MARK: Helpers

    void startCompleted(boolean success);
    void onEvent(WiFiEvent_t event);
    String getMacAddress();

};

#endif
