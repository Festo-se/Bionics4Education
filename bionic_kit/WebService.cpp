
// MARK: Includes

#include "WebService.h"

// MARK: Constants

const String PRINT_PREFIX = "[WEB]: ";

// MARK: Initialization

WebService::WebService() {
  servo_service = ServoService::getSharedInstance();
  dns_service = new DNSService();
  wifi_service = new WiFiService();
}

// MARK: Methods

void WebService::start(IPAddress ip, const uint16_t port, std::function<void(bool)> completion) {
  SPIFFS.begin();

  wifi_service->start(ip, [this, ip, port, completion](boolean success) {
    if (!success) {
      Serial.println(PRINT_PREFIX + "WiFi Setup failed.");
      completion(false);
      return;
    }

    if (!dns_service->start(ip)) {
      Serial.println(PRINT_PREFIX + "DNS Setup failed.");
      completion(false);
      return;
    }

    if (!startWebServer(port)) {
      Serial.println(PRINT_PREFIX + "Webserver Setup failed.");
      completion(false);
      return;
  }

    completion(true);
  });
}

void WebService::loop() {
  boolean has_active_connection = wifi_service->getActiveConnectionCount() > 0;
  if (has_active_connection) {
    dns_service->processRequest();
  }
  servo_service->update(has_active_connection);
}

// MARK: Helpers

boolean WebService::startWebServer(const uint16_t port) {
  // Create and start the webserver with the given port
  server = new AsyncWebServer(port);

  // g_async_web_server_p->serveStatic("/", SPIFFS, "/");
  // Tells the webserver where the website is stored in the internal file system
  // Important to cache the files, because the web server crashes when refreshing the page on mobile devices when files not cashed
  server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setCacheControl("max-age=6000");

  //Handle if the requested file is not found
  server->onNotFound(std::bind(&WebService::handleNotFound, this, std::placeholders::_1));

  // Binds the different requests to the appropriate callback
  //g_async_web_server_p->on("/chat", HTTP_GET, std::bind(&WebService::handleGenerate, this, std::placeholders::_1));
  server->on("/generate_204", HTTP_GET, std::bind(&WebService::handleGenerate, this, std::placeholders::_1));
  server->on("/getWerte", HTTP_GET, std::bind(&WebService::handleUpdateWeb, this, std::placeholders::_1));
  server->on("/setWerte", HTTP_POST, std::bind(&WebService::handleUpdateFromWeb, this, std::placeholders::_1));
  server->on("/switchProject", HTTP_POST, std::bind(&WebService::handleSwitchProject, this, std::placeholders::_1));

  server->begin();

  Serial.println(PRINT_PREFIX + "Async-Web-Server initialized!");

  return true;
}

void WebService::handleGenerate(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Generate 204 answer " + request->url());
  request->send(204, "text/plain", "No Content");
}

void WebService::handleNotFound(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Requested file not found: " + request->url());
  request->send(404, "text/plain", "Not found");
}

void WebService::handleUpdateWeb(AsyncWebServerRequest *request) {
  SliderConfiguration configuration = servo_service->getConfiguration();

  // Make response string with recent stored values
  String response =
    "&value01=" + String(configuration.slider_value_0) +
    "&value02=" + String(configuration.slider_value_1) +
    "&value03=" + String(configuration.slider_value_2) +
    "&value04=" + String(configuration.slider_value_3);

  request->send(200, "text/plain", response);
}

void WebService::handleSwitchProject(AsyncWebServerRequest *request) {

  // Remember all available projects
  const String available_projects[] = {"bionic_fish", "bionic_elephant_trunk", "bionic_chameleon_tongue"};
  const Project projects[] = { fish, elephant, chameleon };

  // Remember the request prefix
  const char* parameter = "activeProject";

  // Get number of arguments in the request
  int32_t argument_count = request->args();

  // Check if there are enough arguments in the request
  if (argument_count != 1) {
    Serial.println(PRINT_PREFIX + "Wrong amount of parameters.");
    request->send(500, "text/plain", "Wrong amount of parameters.");
    return;
  }

  if (!request->hasArg(parameter)) {
    Serial.println(PRINT_PREFIX + "Received a wrong parameter.");
    request->send(500, "text/plain", "Received a wrong parameter.");
    return;
  }

  // Get the get string with the value of the request
  String argument = request->arg(parameter);

  // Loop through all available projects and compare it to the request
  for (int i = 0; i < 3; i++) {
    if (available_projects[i] == argument) {
      servo_service->setProject(projects[i]);
    }
  }

  // Send the new web_values to the homepage (update slider)
  handleUpdateWeb(request);
}

void WebService::handleUpdateFromWeb(AsyncWebServerRequest *request) {

  // Remember the names of the variables from the website
  const String parameters[] = {"value01", "value02", "value03", "value04"};

  // check if there are enough arguments in the request
  int32_t argument_count = request->args();

  if (argument_count != 4) {
    request->send(500, "text/plain", "Zu wenig Parameter!");
    return;
  }

  Serial.println(PRINT_PREFIX + "Website changed slider configuration.");

  SliderConfiguration configuration;

  // Loop through the request and store the values to the internal array
  if (request->hasArg(parameters[0].c_str())) {
    configuration.slider_value_0 = request->arg(parameters[0]).toInt();
  }

  if (request->hasArg(parameters[1].c_str())) {
    configuration.slider_value_1 = request->arg(parameters[1]).toInt();
  }

  if (request->hasArg(parameters[2].c_str())) {
    configuration.slider_value_2 = request->arg(parameters[2]).toInt();
  }

  if (request->hasArg(parameters[3].c_str())) {
    configuration.slider_value_3 = request->arg(parameters[3]).toInt();
  }

  servo_service->setConfiguration(configuration);

  handleUpdateWeb(request);
}
