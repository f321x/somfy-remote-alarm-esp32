#include "somfy_alarm.h"

ESP32Time rtc(3600);
AsyncWebServer server(80);

const char* PARAM_MESSAGE = "param message";


void notFound(AsyncWebServerRequest *request);

void setup() {
    struct tm timeinfo;

    Serial.begin(9600);

    //connect to wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PW);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    configTime(0, 3600, "1.de.pool.ntp.org");
    if (getLocalTime(&timeinfo)){
        rtc.setTimeStruct(timeinfo);
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", WEBSITE);
    });

    // // // Send a GET request to <IP>/get?message=<message>
    // // server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // //     String message;
    // //     if (request->hasParam(PARAM_MESSAGE)) {
    // //         message = request->getParam(PARAM_MESSAGE)->value();
    // //     } else {
    // //         message = "No message sent";
    // //     }
    // //     request->send(200, "text/plain", "Hello, GET: " + message);
    // // });
    server.on("/alarm-time-set", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true))
        {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        }
        else
        {
            message = "No message sent";
        }
        Serial.println(message);
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
  struct tm timeinfo = rtc.getTimeStruct();
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  delay(2000);
}

/*
** Webserver stuff
*/
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

/*
** Somfy stuff
*/


