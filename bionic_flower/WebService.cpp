
// MARK: Includes

#include "WebService.h"

// MARK: Constants

const String PRINT_PREFIX = "[WEB]: ";
const String TEXT_PLAIN = "text/plain";

const String KEY_MOTOR_POSITION = "motor_position";
const String KEY_DISTANCE_THRESHOLD = "distance_threshold";
const String KEY_UPPER_BRIGHTNESS_THRESHOLD = "upper_brightness_threshold";
const String KEY_LOWER_BRIGHTNESS_THRESHOLD = "lower_brightness_threshold";
const String KEY_COLOR = "color";
const String KEY_IS_AUTONOMOUS = "is_autonomous";
const String KEY_BRIGHTNESS = "brightness";
const String KEY_DISTANCE = "distance";
const String KEY_TOUCH_LEFT = "touch_left";
const String KEY_TOUCH_RIGHT = "touch_right";
const String KEY_HAS_TOUCH = "has_touch";
const String KEY_HAS_LIGHT = "has_light";
const String KEY_SPEED = "speed";

// MARK: Initialization

WebService::WebService() {
  hardware_service = HardwareService::getSharedInstance();
  dns_service = new DNSService();
  wifi_service = new WiFiService();
}

// MARK: Methods

void WebService::start(IPAddress ip, const uint16_t port, std::function<void(bool)> completion) {
  SPIFFS.begin();

  if (!hardware_service->start()) {
    Serial.println(PRINT_PREFIX + "Calibration failed.");
    completion(false);
    return;
  }

  wifi_service->start(ip, [this, ip, port, completion](boolean success) {
    if (!success) {
      Serial.println(PRINT_PREFIX + "WiFi setup failed.");
      completion(false);
      return;
    }

    if (!dns_service->start(ip)) {
      Serial.println(PRINT_PREFIX + "DNS setup failed.");
      completion(false);
      return;
    }

    if (!startWebServer(port)) {
      Serial.println(PRINT_PREFIX + "Web setup failed.");
      completion(false);
      return;
    }

    completion(true);
  });
}

void WebService::loop(uint32_t count) {
  boolean has_active_connection = wifi_service->getActiveConnectionCount() > 0;
  /*if (has_active_connection) {
    dns_service->processRequest();
  }*/
  hardware_service->loop(has_active_connection, count);
}

// MARK: Helpers

boolean WebService::startWebServer(const uint16_t port) {

  // Create and start the webserver with the given port
  server = new AsyncWebServer(port);

  // Tells the webserver where the website is stored in the internal file system
  // Important to cache the files, because the web server crashes when refreshing the page on mobile devices when files not cashed
  server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setCacheControl("max-age=6000");

  // Handle if the requested file is not found
  server->onNotFound(std::bind(&WebService::handleNotFound, this, std::placeholders::_1));

  // Bind the different requests to the appropriate callback
  server->on("/generate_204", HTTP_GET, std::bind(&WebService::handleGenerate, this, std::placeholders::_1));
  server->on("/configuration", HTTP_GET, std::bind(&WebService::handleUpdateWeb, this, std::placeholders::_1));
  server->on("/configuration", HTTP_POST, std::bind(&WebService::handleUpdateFromWeb, this, std::placeholders::_1));
  server->on("/calibrate", HTTP_POST, std::bind(&WebService::handleCalibrate, this, std::placeholders::_1));
  server->on("/sensorData", HTTP_GET, std::bind(&WebService::handleReadADC, this, std::placeholders::_1));

  server->begin();

  Serial.println(PRINT_PREFIX + "Async-Web-Server initialized!");

  return true;
}

void WebService::handleGenerate(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Generate 204 answer: " + request->url());
  request->send(204, TEXT_PLAIN, "No Content");
}

void WebService::handleNotFound(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Requested file not found: " + request->url());
  request->send(404, TEXT_PLAIN, "Not found");
}

void WebService::handleCalibrate(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Calibrate");
  hardware_service->resetSensorData();
  handleUpdateWeb(request);
}

void WebService::handleUpdateWeb(AsyncWebServerRequest *request) {
  Configuration configuration = hardware_service->getConfiguration();
  SensorData sensor_data = hardware_service->getSensorData();

  String response =
    KEY_MOTOR_POSITION + "=" + String(configuration.motor_position * 100) + "&" +
    KEY_SPEED + "=" + String(configuration.speed * 100) + "&" +
    KEY_UPPER_BRIGHTNESS_THRESHOLD + "=" + String(configuration.upper_brightness_threshold * 100) + "&" +
    KEY_LOWER_BRIGHTNESS_THRESHOLD + "=" + String(configuration.lower_brightness_threshold * 100) + "&" +
    KEY_DISTANCE_THRESHOLD + "=" + String(configuration.distance_threshold * 100) + "&" +
    KEY_IS_AUTONOMOUS + "=" + String(configuration.is_autonomous ? 1 : 0) + "&" +
    KEY_COLOR + "=" + configuration.color.hexString() + "&" +
    KEY_TOUCH_LEFT + "=" + String(sensor_data.touch_left ? 1 : 0) + "&" +
    KEY_TOUCH_RIGHT + "=" + String(sensor_data.touch_right ? 1 : 0) + "&" +
    KEY_HAS_LIGHT + "=" + String(sensor_data.has_light_sensor ? 1 : 0) + "&" +
    KEY_HAS_TOUCH + "=" + String(sensor_data.has_touch_sensor ? 1 : 0);

  Serial.println(PRINT_PREFIX + "Update web with \"" + response + "\".");
  request->send(200, TEXT_PLAIN, response);
}

void WebService::handleReadADC(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Read sensor data.");
  Configuration configuration = hardware_service->getConfiguration();
  SensorData sensor_data = hardware_service->getSensorData();

  String response =
    KEY_BRIGHTNESS + "=" + String(sensor_data.brightness * 100) + "&" +
    KEY_DISTANCE + "=" + String(sensor_data.distance * 100) + "&" +
    KEY_MOTOR_POSITION + "=" + String(configuration.motor_position * 100) + "&" +
    KEY_SPEED + "=" + String(configuration.speed * 100) + "&" +
    KEY_UPPER_BRIGHTNESS_THRESHOLD + "=" + String(configuration.upper_brightness_threshold * 100) + "&" +
    KEY_LOWER_BRIGHTNESS_THRESHOLD + "=" + String(configuration.lower_brightness_threshold * 100) + "&" +
    KEY_DISTANCE_THRESHOLD + "=" + String(configuration.distance_threshold * 100) + "&" +
    KEY_IS_AUTONOMOUS + "=" + String(configuration.is_autonomous ? 1 : 0) + "&" +
    KEY_COLOR + "=" + configuration.color.hexString() + "&" +
    KEY_TOUCH_LEFT + "=" + String(sensor_data.touch_left ? 1 : 0) + "&" +
    KEY_TOUCH_RIGHT + "=" + String(sensor_data.touch_right ? 1 : 0) + "&" +
    KEY_HAS_LIGHT + "=" + String(sensor_data.has_light_sensor ? 1 : 0) + "&" +
    KEY_HAS_TOUCH + "=" + String(sensor_data.has_touch_sensor ? 1 : 0);

  request->send(200, TEXT_PLAIN, response);
}

void WebService::handleUpdateFromWeb(AsyncWebServerRequest *request) {
  Serial.println(PRINT_PREFIX + "Update configuration from web.");

  Configuration configuration = hardware_service->getConfiguration();

  if (request->hasArg(KEY_MOTOR_POSITION.c_str())) {
    configuration.motor_position = request->arg(KEY_MOTOR_POSITION.c_str()).toFloat() / 100;
  }

  if (request->hasArg(KEY_UPPER_BRIGHTNESS_THRESHOLD.c_str())) {
    configuration.upper_brightness_threshold = request->arg(KEY_UPPER_BRIGHTNESS_THRESHOLD.c_str()).toFloat() / 100;
  }

  if (request->hasArg(KEY_LOWER_BRIGHTNESS_THRESHOLD.c_str())) {
    configuration.lower_brightness_threshold = request->arg(KEY_LOWER_BRIGHTNESS_THRESHOLD.c_str()).toFloat() / 100;
  }

  if (request->hasArg(KEY_DISTANCE_THRESHOLD.c_str())) {
    configuration.distance_threshold = request->arg(KEY_DISTANCE_THRESHOLD.c_str()).toFloat() / 100;
  }

  if (request->hasArg(KEY_IS_AUTONOMOUS.c_str())) {
    configuration.is_autonomous = request->arg(KEY_IS_AUTONOMOUS.c_str()).toInt() > 0;
  }

  if (request->hasArg(KEY_COLOR.c_str())) {
    configuration.color = Color::fromHexString(request->arg(KEY_COLOR.c_str()));
  }

  if (request->hasArg(KEY_SPEED.c_str())) {
    configuration.speed = request->arg(KEY_SPEED.c_str()).toFloat() / 100;
  }

  hardware_service->setConfiguration(configuration);

  handleUpdateWeb(request);
}
