
#ifndef DNSService_H_
#define DNSService_H_

// MARK: Includes

#include <DNSServer.h>
#include "Models.h"

class DNSService {

  public:

    // MARK: Initialization

    DNSService();

    // MARK: Methods

    boolean start(IPAddress ip);
    void processRequest();

  protected:

  private:

    // MARK: Private Properties

    DNSServer* server;

};

#endif
