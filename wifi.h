//defines
#define AUTORESTART_DEBOUNCE_COUNTER    20    //s
#define RECONNECT_TIME                  1000  //ms

//Variables
uint32_t autorestart_debounce_counter = AUTORESTART_DEBOUNCE_COUNTER;

//Function prototypes
void AutoRestartHandler(void);
void setup_wifi(void);
void wifi_connect(const char* ssid, const char* password);


//Functios
void AutoRestartHandler(void)
{
  if(autorestart_debounce_counter > 0)
  {
    autorestart_debounce_counter--;
  }
  if(autorestart_debounce_counter == 0)
  {
    ESP.restart();
    return;
  }
}
void setup_wifi(void)
{
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wifi already connected");
        return;
    }
    
    Serial.print("Try to connect 1st wifi:");
    wifi_connect(ssid, password);
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wifi ssid1 connected");
        return;
    }
}

void wifi_connect(const char* ssid, const char* password)
{
    Serial.println();
    Serial.print("Connecting to: ");
    Serial.print(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(RECONNECT_TIME);
        Serial.print(".");
        AutoRestartHandler();
    }
}
