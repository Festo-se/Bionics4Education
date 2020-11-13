
// MARK: Includes

#include "DNSService.h"

// MARK: Constants

const String PRINT_PREFIX = "[DNS]: ";

const byte DNS_PORT = 53;
const String DNS_FORWARD_NAME = "*";
const int32_t DNS_TTL = 60;

// MARK: Initialization

DNSService::DNSService() {
  server = new DNSServer();
  server->setTTL(DNS_TTL);
  server->setErrorReplyCode(DNSReplyCode::NoError);
}

// MARK: Methods

boolean DNSService::start(IPAddress ip) {
  boolean success = server->start(DNS_PORT, DNS_FORWARD_NAME, ip);

  if (success) {
    Serial.println(PRINT_PREFIX + "Initialization successful.");
  } else {
    Serial.println(PRINT_PREFIX + "Initialization failed.");
  }

  return success;
}

void DNSService::processRequest() {
  server->processNextRequest();
}
