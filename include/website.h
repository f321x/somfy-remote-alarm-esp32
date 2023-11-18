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
