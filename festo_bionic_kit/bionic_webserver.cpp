/**
 * @file     bionic_webserver.cpp
 * 
 * @author   Lucas Schweitzer (lucas.schweitzer@jntec.de)
 * 
 * @brief    This file describes the definition of the class BionicWebserver
 * 
 *  EN: The BionicWebserver Class manages all incomming and outgoing requests regarding the Bionic Website.
 *      The class inherits the Wifi-Setup, DNS-Server and the asynchron Webserver. Furthermore it allows the user to access 
 *      the recent Slider-Values from the Bionic-Website. 
 *  
 *  DE: Die BionicWebserver Klasse  verwaltet alle ein- und ausgehenden Anfragen der Bionic-Webseite. Die Klasse
 *      beinhaltet die Wifi-Setup, den DNS-Server und den asynchronen Webserver. Ausserdem macht sie dem Nutzer die 
 *      aktuellen Slider-Werte der Bionic-Website zugaenglich. 
 *           
 * @date 2018-10-22
 * 
 */


// INCLUDE FILES //
#include "bionic_webserver.h"


const char* WIFI_PASSWORD = "education";            //!< Wifi password for the hotspot 

const byte DNS_PORT = 53;                           //!< Standart port for DNS-Server

const String PRINT_PREFIX = "[BIONIC-WEBSERVER]: "; //!< Prefix for the serial output of the BionicWebserver-Class

/**
 * @brief Constructor of the BionicWebserver class
 * 
 *  EN: Initialize all the necessary member variables at declaration time
 *  DE: Initialisiert alle noetigen Variablen beim Anlegen der Klasse
 * 
 * @param f_port_ui16 EN: Port of the webserver / DE: Port des Webservers
 */
BionicWebserver::BionicWebserver( const uint16_t f_port_ui16)
{      
    m_web_values_a[0] = 0;
    m_web_values_a[1] = 0;
    m_web_values_a[2] = 85;
    m_web_values_a[3] = 0;

    m_active_project_i16 = 0;
    m_new_web_values_b = false;

    m_connections_i16 = 0;

    // IP-Address of the wifi hotspot 
    m_ap_ip = IPAddress(192,168,4,1);

    m_process_counter = 0;
}

/**
 * @brief Method to initialize the wifi hotspot of the esp32
 * 
 *  EN: Method to initialize the wifi hotspot of the esp32 with the generated
 *      SSID based on the mac address of the esp module. The results are
 *      printed to the serial port.
 * 
 *  DE: Die Methode initialisiert den Wifi-Hotspot des ESP32 mit der
 *      entsprechenden SSID basierend auf der MAC-Adresse des Wifi-Moduls.
 *      Abschliesend wird der Status ueber den seriellen Port ausgegeben.  
 */
void BionicWebserver::initWifi()
{
    // Generating the unique SSID
    String wifi_ssid_s = "b4e_" + getMacAddress();
    
    // Set HOTSPOT Mode
    WiFi.mode(WIFI_AP);    
   
   // Setting the IP-Address
    WiFi.softAPConfig(m_ap_ip, m_ap_ip, IPAddress(255, 255, 255, 0));  
    delay(250);
  
    // Setup the Wifi with SSID, PW, Channel, IsHidden, Allowed Connections
    WiFi.softAP(wifi_ssid_s.c_str(), WIFI_PASSWORD, 6, 0, 1);
    IPAddress myIP = WiFi.softAPIP();
    delay(250);
    
    // Print all results to the serial port
    Serial.println(PRINT_PREFIX + "Wifi ready!");
    Serial.println(PRINT_PREFIX + "MAC-Address: "+ getMacAddress());
    Serial.print(PRINT_PREFIX + "HotSpot IP: ");
    Serial.println(myIP);
    Serial.println(PRINT_PREFIX + "WifiSSID: " + String(wifi_ssid_s));
}

/**
 * @brief Method to initialize the dns server
 * 
 *  EN: Method to initialize the dns server in a way that it is possible for
 *      the user to type in any webaddress in the browser and will always be 
 *      redirected to the bionic website.
 * 
 *  DE: Methode initialisiert den DNS-Server. Der DNS-Server wird so konfiguriert,
 *      dass der Nutzer immer zu Bionic-Webseite weitergeleitet wird, egal welche 
 *      Eingabe er im Adressfeld des Browsers taetigt. 
 */
void BionicWebserver::initDNS()
{
    // Setup the dns server
    m_dns_server.setTTL( 300 );
    m_dns_server.setErrorReplyCode( DNSReplyCode::ServerFailure );
    
    // The '*' parameter redirects all incomming requests to the webserver
    // independent of the input in the address bar of the browser.
    m_dns_server.start( DNS_PORT, "*", m_ap_ip );

    Serial.println(PRINT_PREFIX + "DNS-Server initialized!");
}

/**
 * @brief Method to initialize the asynchron webserver for the bionic homepage
 * 
 *  EN: Method to initialize the asynchron webserver for the bionic homepage and sets all
 *      necessary callbacks
 * 
 *  DE: Methode initialisiert den Asynchronen-Webserver fuer die Bionic-Webseite und setzt
 *      alle noetigen callbacks. 
 * 
 * @param f_port_ui16  EN: Webserver Port / DE: Port des Webservers. 
 */
void BionicWebserver::initWebserver( const uint16_t f_port_ui16 )
{
    // Create and start the webserver with the given port
    g_async_web_server_p = new AsyncWebServer(f_port_ui16); 
    
    //g_async_web_server_p->serveStatic("/", SPIFFS, "/");
    // Tells the webserver where the website is stored in the internal file system
    //Important to cache the files, because the web server crashes when refreshing the page on mobile devices when files not cashed
    g_async_web_server_p->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setCacheControl("max-age=6000");

    //Handle if the requested file is not found
    g_async_web_server_p->onNotFound(std::bind(&BionicWebserver::handleNotFound, this, std::placeholders::_1 ));
    
    // Binds the different requests to the appropriate callback
    //g_async_web_server_p->on("/chat", HTTP_GET, std::bind(&BionicWebserver::handleGenerate, this, std::placeholders::_1 ));
    g_async_web_server_p->on("/generate_204", HTTP_GET, std::bind(&BionicWebserver::handleGenerate, this, std::placeholders::_1 ));
    g_async_web_server_p->on("/getWerte", HTTP_GET, std::bind(&BionicWebserver::handleUpdateWebVal, this, std::placeholders::_1 ));
    g_async_web_server_p->on("/setWerte", HTTP_POST, std::bind(&BionicWebserver::handleUpdateEspValFromWeb, this, std::placeholders::_1 ));
    g_async_web_server_p->on("/switchProject", HTTP_POST, std::bind(&BionicWebserver::handleSwitchProject, this, std::placeholders::_1 ));

    g_async_web_server_p->begin();

    Serial.println(PRINT_PREFIX + "Async-Web-Server initialized!");
    
}

/**
 * @brief Method initialize the complete Bionic-Webserver with wifi, dns and async webserver
 * 
 *  EN: Method initialize all necessary components of the Bionic-Webserver like wifi, dns and 
 *      async webserver. Furthermore the internal filesystem is initialized. 
 * 
 *  DE: Methode initialisiert alle noetigen Komponenten des Bionic-Webservers wie Wifi-Hotspot,
 *      DNS-Server und Asynchroner Webserver. Ausserdem wird das interne Filesystem des ESPs 
 *      initialisiert. 
 * 
 * @param f_port_ui16  EN: Webserver Port / DE: Port des Webservers. 
 */
void BionicWebserver::init( const uint16_t f_port_ui16 )
{
    // Start wifi
    initWifi();
      
    // Initialize the internal filesystem
    if (!SPIFFS.begin())
    {
      Serial.println(PRINT_PREFIX + "SPIFFS not initialized! Stop!");
      while (1) yield();
    }
    Serial.println(PRINT_PREFIX + "SPIFFS initialized!");

    // Start DNS
    initDNS();

    // Run webserver with given port 
    initWebserver( f_port_ui16 );
    
    //m_proces_timer_p = new Ticker();
    //m_proces_timer_p->attach(0.5 , std::bind(&BionicWebserver::dnsProcessNextRequest,this));
}

/**
 * @brief Method keeps the dns server alive and counts the connected clients on the wifi hotspot
 * 
 *  EN: Function has to be called in the main loop of the program to process all incomming
 *      dns requests on the specified DNS_PORT. Furthermore the method counts all 
 *      connected client on the wifi hotspot and prints the number to the serial port. 
 * 
 *  DE: Diese Funktion triggert die Anfragen-Bearbeitung des DNS-Server am spezifizierten DNS_PORT.
 *      Ausserdem zaehlt sie die Clients die mit dem Wifi-Hotspot verbunden sind und gibt die Anzahl
 *      ueber den Seriellen-Port aus. Funktion muss zyklisch im Hauptprogramm aufgerufen werden.      
 * 
 */
void BionicWebserver::processRequests()
{    
    if((m_process_counter % 500) == 0)
    {
      m_dns_server.processNextRequest();
      
      int16_t new_connections_i16 = WiFi.softAPgetStationNum();
      if (new_connections_i16 != m_connections_i16)
      {
        Serial.println(PRINT_PREFIX + "Clients connected: " + new_connections_i16);
        m_connections_i16 = new_connections_i16;
      }
    
    }    
    m_process_counter++;
}


/**
 * @brief Method prints all stored slider values
 * 
 *  EN: Method prints all stored slider values from the bionic website on the serial monitor
 * 
 *  DE: Methode gibt alle gespeicherten Slider-Werte der Bionic Website ueber den seriellen
 *      Port aus. 
 * 
 */
void BionicWebserver::printValues(void)
{
  Serial.print(PRINT_PREFIX +"Slider 1 Value: ");
  Serial.println(m_web_values_a[0], DEC);

  Serial.print(PRINT_PREFIX +"Slider 2 Value: ");
  Serial.println(m_web_values_a[1], DEC);

  Serial.print(PRINT_PREFIX +"Slider 3 Value: ");
  Serial.println(m_web_values_a[2], DEC);

  Serial.print(PRINT_PREFIX +"Slider 4 Value: ");
  Serial.println(m_web_values_a[3], DEC);
}



void BionicWebserver::handleGenerate(AsyncWebServerRequest *f_request_p)
{
  //Serial.println(PRINT_PREFIX +"Generate 204 answer " + f_request_p->url() );
  f_request_p->send(204, "text/plain", "No Content");

}

/**
 * @brief Callback handle if requested file is not found
 * 
 *  EN: Callback handle for webserver if requested file is not found
 * 
 *  DE: Callback handle des Webservers wenn das angeforderte Dokument nicht vorhanden ist
 * 
 * @param f_request_p EN: Recent webserver request / DE: Aktuelle Webserver Anfrage
 */
void BionicWebserver::handleNotFound(AsyncWebServerRequest *f_request_p)
{
  //Serial.println(PRINT_PREFIX +"Requested file not found: " + f_request_p->url() );
  f_request_p->send(404, "text/plain", "Not found");

}

/**
 * @brief Callback handle for updating the Bionic Website
 * 
 *  EN: Callback handle for updating the Bionic Website (Slider Values) with the 
 *      stored values in the class
 * 
 *  DE: Callback handle um die Slider-Werte der Bionic-Webseite zu aktualisieren. 
 *      Fuer die Aktualisierung werden die gespeicherten Werte innerhalb der Klasse genutzt. 
 * 
 * @param f_request_p EN: Recent webserver request / DE: Aktuelle Webserver Anfrage
 */
void BionicWebserver::handleUpdateWebVal(AsyncWebServerRequest *f_request_p)
{
  //Serial.println(PRINT_PREFIX +"Request host: " + f_request_p->host() );
  //Serial.println(PRINT_PREFIX +"Requested url: " + f_request_p->url() );
  //Serial.println(PRINT_PREFIX +"Requested url: " + f_request_p->contentLength() );
  // Make response string with recent stored values
  String req_s = "&value01=" + String(m_web_values_a[0]) + 
                 "&value02=" + String(m_web_values_a[1]) + 
                 "&value03=" + String(m_web_values_a[2]) + 
                 "&value04=" + String(m_web_values_a[3]);
  
  f_request_p->send(200, "text/plain", req_s);
}

/**
 * @brief Callback handle when the project is switched on the Bionic Website by the user
 * 
 *  EN: Callback handle when the project (fish, elephant_trunk, chameleon_tongue ) is switched on 
 *      the Bionic Website by the user. Initialize the shown website with proper values. 
 * 
 *  DE: Callback handle um die Slider-Werte der Bionic-Webseite zu aktualisieren wenn der Nutzer 
 *      zwischen den verschiedenen Projekten (fish, elephant_trunk, chameleon_tongue ) wechselt. 
 * 
 * @param f_request_p EN: Recent webserver request / DE: Aktuelle Webserver Anfrage
 */
void BionicWebserver::handleSwitchProject(AsyncWebServerRequest *f_request_p)
{

  // Remember all available projects
  const String available_projects_a[] = {"bionic_fish", "bionic_elephant_trunk", "bionic_chameleon_tongue"};

  // Remember the request prefix
  const char* param_s = "activeProject";
 
  // Get number of arguments in the request
  int32_t num_i32 = f_request_p->args();

  // Check if there are enough arguments in the request
  if (num_i32 != 1)
  {
    Serial.println(PRINT_PREFIX + "Wrong amount of parameters.");
    f_request_p->send(500, "text/plain", "Wrong amount of parameters.");
    return;
  }
  
  // Check if its the right request 
  if (f_request_p->hasArg(param_s))
  { 

    // Get the get string with the value of the request
    String web_server_arg_s = (f_request_p->arg(param_s));

    // Loop through all available projects and compare it to the request
    for (int i = 0; i < 3; i++)
    {
      if (available_projects_a[i] == web_server_arg_s)
      {        
        // Set the found project as new active project
        m_active_project_i16 = i;

        // Initialize the web_values properly based on the active project
        switch (m_active_project_i16)
        {
          // Fish
          case 0:
            {
              m_web_values_a[0] = 0;
              m_web_values_a[1] = 0;
              m_web_values_a[2] = 85;
              m_web_values_a[3] = 0;
              Serial.println("");
              Serial.println(PRINT_PREFIX + "Web GUI: Bionic Fish");
              break;
            }
          // Elephant trunk
          case 1:
            {
              m_web_values_a[0] = 30;
              m_web_values_a[1] = 30;
              m_web_values_a[2] = 30;
              m_web_values_a[3] = 30;
              Serial.println("");
              Serial.println(PRINT_PREFIX + "Web GUI: Bionic Elephant");
              break;
            }
          // Chameleon tongue
          case 2:
            {
              m_web_values_a[0] = 90;
              m_web_values_a[1] = 90;
              m_web_values_a[2] = 90;
              m_web_values_a[3] = 90;
              Serial.println("");
              Serial.println(PRINT_PREFIX + "Web GUI: Bionic Chameleon");
              break;
            }
        }

              
      
      }
    }

  }
  else
  {
    Serial.println(PRINT_PREFIX + "Received a wrong parameter.");
    f_request_p->send(500, "text/plain", "Received a wrong parameter.");
  }

  // Send the new web_values to the homepage (update slider)
  handleUpdateWebVal(f_request_p);
  
  
  
  // Rise the flag for new values
  m_new_web_values_b = true; 

}

/**
 * @brief Callback handle if the user sets new slider values 
 *  
 *  EN: Callback handle if the user sets new slider values on the bionic website (on slider release).
 *      Method stores the new values from the website.
 * 
 *  DE: Callback wenn der Nutzer neue Slider-Werte auf der Webseite einstellt. Neue Werte werden
 *      gespeichert damit sie außerhalb der Klasse zugaenglich sind. 
 * 
 * 
 * @param f_request_p Recent webserver request / DE: Aktuelle Webserver Anfrage
 */
void BionicWebserver::handleUpdateEspValFromWeb(AsyncWebServerRequest *f_request_p)
{
  // Remember the names of the variables from the website 
  const String params_a[] = {"value01", "value02", "value03", "value04"};

  // check if there are enough arguments in the request
  int32_t num_i32 = f_request_p->args();
  if (num_i32 != 4)
  {
    f_request_p->send(500, "text/plain", "Zu wenig Paramater!");
    return;

  }

  // Loop through the request and store the values to the internal array
  for (int i = 0; i < 4; i++)
  {
    if (f_request_p->hasArg(params_a[i].c_str()))
    {
      m_web_values_a[i] = f_request_p->arg(params_a[i]).toInt();
      //Serial.println(PRINT_PREFIX +"m_web_values: " + i+ ": "+ m_web_values_a[i] );
    }
  }

  Serial.println(PRINT_PREFIX + "New values from website");
  //printValues();
  
  // Rise the flag for new values
  m_new_web_values_b = true;
  
  // Update the website to keep in sync 
  handleUpdateWebVal(f_request_p);

}

/**
 * @brief Method reads the MAC-Address from the internal register
 * 
 *  EN: Method reads the MAC-Address from the internal register and returns it 
 *      as as string
 * 
 *  DE: Methode liest die MAC-Adresse aus dem internen Register des ESPs aus und 
 *      gibt sie als String zurück
 * 
 * @return String EN: MAC-Address as string / DE: MAC-Adresse als String
 */
String BionicWebserver::getMacAddress()
{
  uint8_t base_mac_a[6];
  esp_read_mac(base_mac_a, ESP_MAC_WIFI_STA);
  char base_mac_chr_a[18] = {0};
  sprintf(base_mac_chr_a, "%02X_%02X_%02X_%02X_%02X_%02X", base_mac_a[0], base_mac_a[1], base_mac_a[2], base_mac_a[3], base_mac_a[4], base_mac_a[5]);

  return String(base_mac_chr_a);
}
