//Function prototypes
void check_OTA(void);

//Functions
void check_OTA(void)
{
    // setup_wifi(); must be called before check_OTA();
    Serial.print("Firmware:<");
    Serial.print(FW_VERSION);
    Serial.println(">");
    Serial.println("Check for OTA");
    HTTPClient http;
    if (http.begin(fwVersionURL)) {
        Serial.println("http begin");
        int httpCode = http.GET();
        Serial.print("httpCode:");
        Serial.println(httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String newFWVersion = http.getString();
            Serial.print("Server  FWVersion: ");
            Serial.print(newFWVersion);
            Serial.print(" / ");
            Serial.print("Current FWVersion: ");
            Serial.println(FW_VERSION);
            float newVersion = newFWVersion.toFloat();
            if (newVersion > FW_VERSION) {
                Serial.println("start OTA !");
                http.end();
                delay(100);
                t_httpUpdate_return ret = ESPhttpUpdate.update(fwImageURL);
                switch (ret) {
                case HTTP_UPDATE_FAILED:
                    Serial.print("HTTP_UPDATE_FAILD Error");
                    Serial.print(ESPhttpUpdate.getLastError());
                    Serial.print(": ");
                    Serial.println(ESPhttpUpdate.getLastErrorString().c_str());
                    //USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                    break;
                case HTTP_UPDATE_NO_UPDATES:
                    Serial.println("HTTP_UPDATE_NO_UPDATES");
                    break;
                case HTTP_UPDATE_OK:
                    Serial.println("HTTP_UPDATE_OK");
                    break;
                }
            } else {
                Serial.println("no new version available");
            }
        }
    }
    Serial.println("End of OTA");
}
