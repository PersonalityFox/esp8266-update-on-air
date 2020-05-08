// File to download with the extension * .bin (Sketch-> Export binary file)

/* OTA BLOCK BEGIN */
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
#include <ESP8266WiFi.h>
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h
#include <ESP8266WebServer.h>
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPUpdateServer/src/ESP8266HTTPUpdateServer.h
#include <ESP8266HTTPUpdateServer.h>

const char* ssid =     "Free Wi-Fi";      //  SSID your wifi
const char* password = "**********";      // Password your wi-fi

#define OTAUSER         "admin"           // Login for OTA
#define OTAPASSWORD     "admin"           // Password for OTA
#define OTAPATH         "/firmware"       // Path to download firmware
#define SERVERPORT      80                // Port OTA

ESP8266WebServer HttpServer(SERVERPORT);
ESP8266HTTPUpdateServer HttpUpdater;
/* OTA BLOCK END */

// any code
// ...

void setup(void) {
  /* OTA BLOCK BEGIN */
  WiFi.begin(ssid, password);
  
  // Waiting for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  
  HttpUpdater.setup(&HttpServer, OTAPATH, OTAUSER, OTAPASSWORD);
  HttpServer.onNotFound(handleNotFound);
  HttpServer.begin();
  /* OTA BLOCK END */

  // any code
  // ...
}

/* OTA BLOCK BEGIN */
void loop(void) {
  HttpServer.handleClient();            // HTTP request handler
}

// Send 404 if http request not found
void handleNotFound() {
  HttpServer.send(404, "text/plain", "404: Not found");
}
/* OTA BLOCK END */
