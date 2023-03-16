
// MARK: Includes

#include "WiFiService.h"

// MARK: Constants

const char* WIFI_PASSWORD = "education";
const String PRINT_PREFIX = "[WiFi]: ";
const IPAddress SUBNETMASK = IPAddress(255, 255, 255, 0);
const int CHANNEL = 6;
const boolean IS_HIDDEN = false;
const int MAX_CONNECTIONS = 4;

namespace{
	uint8_t findGoodChannel() {
	  WiFi.mode(WIFI_STA);
	  WiFi.disconnect();
	  uint32_t n = WiFi.scanNetworks();
	  if (n > 0) {
		uint32_t bandCounts[3] = {0};
		for (uint32_t i = 0; i < n; ++i) {
		  uint8_t channel = WiFi.channel(i);
		  if (channel < 4) {
			bandCounts[0]++;
		  } else if (channel < 9) {
			bandCounts[1]++;
		  } else if (channel < 14) {
			bandCounts[2]++;
		  }
		}
		uint32_t minBandCount = UINT32_MAX;
		uint8_t minBandIndex = UINT32_MAX;
		for (uint8_t i = 0; i < 3; ++i) {
		  if (bandCounts[i] < minBandCount) {
			minBandCount = bandCounts[i];
			minBandIndex = i;
		  }
		}
		switch (minBandIndex) {
		  case 0: return 1;
		  case 1: return 6;
		  case 2: return 11;
		}
	  }
	  return 6;
	}
}

// MARK: Initialization

WiFiService::WiFiService() {
  this->start_completion = [](boolean success) {
    return;
  };
}

// MARK: Methods

void WiFiService::start(IPAddress ip, std::function<void(bool)> completion) {
  this->ip_address = ip;
  this->start_completion = completion;

  WiFi.onEvent(std::bind(&WiFiService::onEvent, this, std::placeholders::_1));

  String ssid = "b4e_" + getMacAddress();
  uint8_t channel = findGoodChannel();
  
  Serial.println(PRINT_PREFIX + "Starting softAP.");
  if (!WiFi.softAP(ssid.c_str(), WIFI_PASSWORD, channel, false, MAX_CONNECTIONS)) {
    Serial.println(PRINT_PREFIX + "AP setup failed.");
    startCompleted(false);
    return;
  }
}

int WiFiService::getActiveConnectionCount() {
  return WiFi.softAPgetStationNum();
}

// MARK: Helpers

void WiFiService::startCompleted(boolean success) {
  this->start_completion(success);
  this->start_completion = [](boolean success) {
    return;
  };
}

void WiFiService::onEvent(WiFiEvent_t event) {
  switch (event) {
    case SYSTEM_EVENT_WIFI_READY:
      Serial.println(PRINT_PREFIX + "Event: Wifi ready!");
      break;
    case SYSTEM_EVENT_SCAN_DONE:
      Serial.println(PRINT_PREFIX + "Event: Scan done!");
      break;
    case SYSTEM_EVENT_STA_START:
      Serial.println(PRINT_PREFIX + "Event: Station started");
      break;
    case SYSTEM_EVENT_STA_STOP:
      Serial.println(PRINT_PREFIX + "Event: Station stopped!");
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println(PRINT_PREFIX + "Event: Station connected!");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println(PRINT_PREFIX + "Event: Station disconnected!");
      break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
      Serial.println(PRINT_PREFIX + "Event: Station auth mode changed!");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println(PRINT_PREFIX + "Event: Station got IP!");
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
      Serial.println(PRINT_PREFIX + "Event: Station lost IP!");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println(PRINT_PREFIX + "Event: Station WPS Enrollee Mode successful!");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println(PRINT_PREFIX + "Event: Station WPS Enrollee Mode failed!");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println(PRINT_PREFIX + "Event: Station WPS Enrollee Mode timed out!");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
      Serial.println(PRINT_PREFIX + "Event: Station WPS Enrollee Mode PIN!");
      break;
    case SYSTEM_EVENT_AP_START:
      Serial.println(PRINT_PREFIX + "Event: AP started!");
      Serial.println(PRINT_PREFIX + "MAC-Address: " + getMacAddress());
      Serial.println(PRINT_PREFIX + "HotSpot IP: " + ip_address.toString());
      startCompleted(true);
      break;
    case SYSTEM_EVENT_AP_STOP:
      Serial.println(PRINT_PREFIX + "Event: AP stopped!");
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      Serial.println(PRINT_PREFIX + "Event: AP - Station connected!");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      Serial.println(PRINT_PREFIX + "Event: AP - Station disconnected!");
      break;
    case SYSTEM_EVENT_AP_STAIPASSIGNED:
      Serial.println(PRINT_PREFIX + "Event: AP - Station IP assigned!");
      break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
      Serial.println(PRINT_PREFIX + "Event: AP - Probe request received!");
      break;
    case SYSTEM_EVENT_GOT_IP6:
      Serial.println(PRINT_PREFIX + "Event: IPv6 preferred!");
      break;
    case SYSTEM_EVENT_ETH_START:
      Serial.println(PRINT_PREFIX + "Event: Ethernet started!");
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println(PRINT_PREFIX + "Event: Ethernet stopped!");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Serial.println(PRINT_PREFIX + "Event: Ethernet link up!");
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println(PRINT_PREFIX + "Event: Ethernet link down!");
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Serial.println(PRINT_PREFIX + "Event: Ethernet got IP!");
      break;
    default:
      Serial.println(PRINT_PREFIX + "Event: Unknown!");
      break;
  }
}

String WiFiService::getMacAddress() {
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  return mac.substring(8, 12);
}
