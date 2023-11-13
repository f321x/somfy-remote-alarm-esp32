#include <Arduino.h>

#include <EEPROM.h>
#include <EEPROMRollingCodeStorage.h>
#include <SomfyRemote.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Time.h>
#include <ArduinoJson.h>


#define EMITTER_GPIO 2
#define EEPROM_ADDRESS 0
#define REMOTE 0x5184c8
#define CC1101_FREQUENCY 433.42

#define WIFI_SSID "Steuern sind Raub"
#define WIFI_PW "npsr2azPmddm"

// https://github.com/Legion2/Somfy_Remote_Lib
