/**
 * @file     bionic_webserver.h
 * 
 * @author   Lucas Schweitzer (lucas.schweitzer@jntec.de)
 * 
 * @brief    This file describes the declaration of the class BionicWebserver
 * 
 *  EN: The BionicWebserver Class manages all incomming and outgoing requests regarding the Bionic Website.
 *      The class inherits the Wifi-Setup, DNS-Server and the asynchron Webserver. Furthermore it allows the user to access 
 *      the recent Slider-Values from the Bionic-Website. 
 *  
 *  DE: Die BionicWebserver Klasse verwaltet alle ein- und ausgehenden Anfragen der Bionic-Webseite. Die Klasse
 *      beinhaltet die Wifi-Setup, den DNS-Server und den asynchronen Webserver. Ausserdem macht sie dem Nutzer die 
 *      aktuellen Slider-Werte der Bionic-Website zugaenglich. 
 *           
 * @date 2018-10-22
 * 
 */


// Include guard //
#ifndef BIONIC_WEBSERVER_H_   
#define BIONIC_WEBSERVER_H_

// INCLUDE FILES //
#include <DNSServer.h>
#include <FS.h> // muss vor <detail\RequestHandlersImpl.h> stehen 
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <algorithm>
#include <string>
#include "esp_system.h"
#include <Ticker.h>


class BionicWebserver
{
  public:
    BionicWebserver( const uint16_t f_port_ui16);

    void init( const uint16_t f_port_ui16 );
    void printValues(void);
    void processRequests();
    String getMacAddress();

    /**
     * @brief Get the Active Connections object
     * 
     * @return uint16_t EN: Number of active clients DE: Anzahl aktiver Verbindungen
     */
    uint16_t getActiveConnections() const {return m_connections_i16;}

    /**
     * @brief Get the Active Project Id 
     * 
     * @return int16_t EN: recent selected project DE: Zuletzt ausgewaehltes Projekt
     */
    int16_t getActiveProjectId() const {return m_active_project_i16;}

    /**
     * @brief Get if there are new webserver values
     *
     *  EN: True if there are new values available
     *  DE: True wenn neue Werte verfuegbar
     * 
     *  EN: False if there are no new values or if the user already
     *      fetched them.
     *  DE: Nicht Wahr, wenn keine neuen Werte vorliegen oder sie bereits
     *      abgerufen wurden. 
     * 
     * @return true 
     * @return false 
     */
    bool isNewWebValue() const {return m_new_web_values_b;}

    /**
     * @brief Get the most recent Website-Values as array
     * 
     *  EN: Get the most recent Website-Values as array of size [4]
     *  DE: Liefert die aktuellsten Werte der Webseite zurueck. 
     * 
     */
    int16_t ( &getWebValues( int16_t (&arr)[4] ) )[4] 
    {
      arr[0] = m_web_values_a[0];
      arr[1] = m_web_values_a[1];
      arr[2] = m_web_values_a[2];
      arr[3] = m_web_values_a[3];

      m_new_web_values_b = false;
       
      return arr;
    }

    /**
     * @brief Sets the array for the Website values 
     * 
     * EN: Allows the user to set the Array for the Website values from 
     *     outside the class. 
     * DE: Erlaubt es das Array mit den Werten fuer die Webseite
     *     von ausserhalb zu fuellen. 
     * 
     */
    void updateWebValues( int16_t (&updateValues)[4])
    {
      m_web_values_a[0] = updateValues[0];
      m_web_values_a[1] = updateValues[1];
      m_web_values_a[2] = updateValues[2];
      m_web_values_a[3] = updateValues[3];

    }


  protected:      
    AsyncWebServer *g_async_web_server_p;     //!< Pointer to the AsyncWebServer
    void handleNotFound(AsyncWebServerRequest *f_request_p);
    void handleUpdateWebVal(AsyncWebServerRequest *f_request_p);
    void handleSwitchProject(AsyncWebServerRequest *f_request_p);
    void handleUpdateEspValFromWeb(AsyncWebServerRequest *f_request_p); 
    void handleGenerate(AsyncWebServerRequest *f_request_p);   
     
  private:    
    DNSServer m_dns_server;                 //!< DNS-Server object
        
    int16_t m_web_values_a[4];              //!< Array which stores the recent slider values

    int16_t m_active_project_i16;           //!< Stores the actual selected project id on the website

    bool m_new_web_values_b;                //!< Flag to notify if there are new slider values available
    bool initiated_b;                       //!< Flag if the webserver is already initialized 
    
    int16_t m_connections_i16;               //!< Number of connected clients to the wifi hotspot

    int32_t m_process_counter;              //!< Call Counter for the DNS Request 

    IPAddress m_ap_ip;                      //!< IP-Address of the wifi hotspot default: 192.168.4.1

    void initWifi();
    void initDNS();
    void initWebserver(const uint16_t f_port_ui16);
    //Ticker *m_proces_timer_p;

};
#endif
