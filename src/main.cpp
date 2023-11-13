#include "somfy_alarm.h"

ESP32Time rtc(3600);
AsyncWebServer server(80);

const char* PARAM_MESSAGE = "param message";
const char* WEBSITE =  R"rawliteral(<!DOCTYPE html>
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

        var data = { time: timeInput };
            fetch('/alarm-time-set', {
            method: 'POST',     // HTTP method
            headers: {
                'Content-Type': 'application/json',  // Data type being sent
            },
            body: JSON.stringify(data),  // Convert the JavaScript object to a JSON string
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
                return response.json();  // or response.text() if the response is not in JSON format
            })
            .then(data => {
                console.log('Success:', data);  // Handle success here
            })
            .catch((error) => {
                console.error('Error:', error);  // Handle errors here
            })};
</script>
</head>
<body>
    <h1>Somfy Alarm Clock</h1>
    <p>Set the alarm time:</p>
    <input type="time" id="timeInput">
    <button onclick="setAlarm()">Set Alarm</button>
    <h2>Current Alarm Time: <span id="alarmTime"></span></h2>
</body>
</html>
)rawliteral";

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


