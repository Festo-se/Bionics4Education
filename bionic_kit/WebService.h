
#ifndef BIONIC_WEBSERVER_H_
#define BIONIC_WEBSERVER_H_

// MARK: Includes

#include <ESPAsyncWebServer.h>
#include "Models.h"
#include "DNSService.h"
#include "ServoService.h"
#include "WiFiService.h"

class WebService {

  public:

    // MARK: Initialization

    WebService();

    // MARK: Methods

    void start(IPAddress ip, const uint16_t port, std::function<void(bool)> completion);
    void loop();

  protected:

  private:

    // MARK: Private Properties

    DNSService* dns_service;
    ServoService* servo_service;
    WiFiService* wifi_service;
    AsyncWebServer *server;

    // MARK: Helpers

    boolean startWebServer(const uint16_t port);

    void handleNotFound(AsyncWebServerRequest *request);
    void handleGenerate(AsyncWebServerRequest *request);
    void handleSwitchProject(AsyncWebServerRequest *request);

    void handleUpdateWeb(AsyncWebServerRequest *request);
    void handleUpdateFromWeb(AsyncWebServerRequest *request);

};

#endif
