
#ifndef BIONIC_WEBSERVER_H_
#define BIONIC_WEBSERVER_H_

// MARK: Includes

#include <ESPAsyncWebServer.h>
#include "Models.h"
#include "DNSService.h"
#include "HardwareService.h"
#include "WiFiService.h"

class WebService {

  public:

    // MARK: Initialization

    WebService();

    // MARK: Methods

    void start(IPAddress ip, const uint16_t port, std::function<void(bool)> completion);
    void loop(uint32_t count);

  protected:

  private:

    // MARK: Private Properties

    boolean has_started = false;

    DNSService* dns_service;
    HardwareService* hardware_service;
    WiFiService* wifi_service;
    AsyncWebServer *server;

    // MARK: Helpers

    boolean startWebServer(const uint16_t port);

    void handleNotFound(AsyncWebServerRequest *request);
    void handleGenerate(AsyncWebServerRequest *request);
    void handleReadADC(AsyncWebServerRequest *request);
    void handleCalibrate(AsyncWebServerRequest *request);

    void handleUpdateWeb(AsyncWebServerRequest *request);
    void handleUpdateFromWeb(AsyncWebServerRequest *request);
    
};

#endif
