//FW version
const float FW_VERSION = 0.2;

//Includes
#include "credentials.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "ESP32httpUpdate.h"
#include "ota.h"
#include "wifi.h"

void setup()
{
  Serial.begin(115200);
  //ESP.eraseConfig();
  WiFi.disconnect();
  setup_wifi();
  check_OTA();
  delay(25);
  WiFi.disconnect();
}

void loop()
{
  Serial.println("Loop");
  delay(1000);
}
