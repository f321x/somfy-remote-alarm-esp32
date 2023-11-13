#include "somfy_alarm.h"

ESP32Time rtc(3600);
// AsyncWebServer server(80);

const char* PARAM_MESSAGE = "param message";
const char* WEBSITE =  R"rawliteral("<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alarm Clock</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
        }
        #alarmTime {
            font-size: 1.5em;
        }
    </style>
    <script>
        function setAlarm() {
            var timeInput = document.getElementById('timeInput').value;
            document.getElementById('alarmTime').innerText = timeInput;
            // Send this time to the ESP32 for further processing
            // This could be an AJAX call to a REST endpoint on the ESP32
        }

        // This function would be used to make an AJAX call to the ESP32
        // to retrieve the current set alarm time when the page loads
        function getAlarmTime() {
            // Placeholder for AJAX call to get the alarm time from ESP32
            var currentAlarmTime = 'Not set'; // This should be replaced with the actual value from ESP32
            document.getElementById('alarmTime').innerText = currentAlarmTime;
        }

        // Call getAlarmTime on page load to show the current alarm time
        window.onload = getAlarmTime;
    </script>
</head>
<body>
    <h1>ESP32 Alarm Clock</h1>
    <p>Set the alarm time:</p>
    <input type="time" id="timeInput">
    <button onclick="setAlarm()">Set Alarm</button>
    <h2>Current Alarm Time: <span id="alarmTime"></span></h2>
</body>
</html>
)rawliteral";

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

    configTime(3600, 3600, "1.de.pool.ntp.org");
    if (getLocalTime(&timeinfo)){
        rtc.setTimeStruct(timeinfo);
    }

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //     request->send(200, "text/plain", "Hello, world");
    // });

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

    // // // Send a POST request to <IP>/post with a form field message set to <message>
    // // server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
    // //     String message;
    // //     if (request->hasParam(PARAM_MESSAGE, true)) {
    // //         message = request->getParam(PARAM_MESSAGE, true)->value();
    // //     } else {
    // //         message = "No message sent";
    // //     }
    // //     request->send(200, "text/plain", "Hello, POST: " + message);
    // // });

    // server.onNotFound(notFound);

    // server.begin();
}

void loop() {

  struct tm timeinfo = rtc.getTimeStruct();
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  delay(2000);
}

/*
** Webserver stuff
*/
// void notFound(AsyncWebServerRequest *request) {
//     request->send(404, "text/plain", "Not found");
// }

/*
** Somfy stuff
*/


