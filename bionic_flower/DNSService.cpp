
// MARK: Includes

#include "DNSService.h"
#include "dns_hijack_srv.h"

// MARK: Constants

const String PRINT_PREFIX = "[DNS]: ";

const byte DNS_PORT = 53;
const String DNS_FORWARD_NAME = "*";
const int32_t DNS_TTL = 60;

// MARK: Initialization

DNSService::DNSService() {
  //server = new DNSServer();
  //server->setTTL(DNS_TTL);
  //server->setErrorReplyCode(DNSReplyCode::NoError);
}

// MARK: Methods

boolean DNSService::start(IPAddress ip) {
    ip4_addr_t resolve_ip;
    inet_pton(AF_INET, "192.168.4.1", &resolve_ip);
    
    boolean success = (dns_hijack_srv_start(resolve_ip) == ESP_OK);

    if (success) {
    Serial.println(PRINT_PREFIX + "Initialization successful.");
    } else {
    Serial.println(PRINT_PREFIX + "Initialization failed.");
    }

  return success;
}

//void DNSService::processRequest() {
  //server->processNextRequest();
//}
