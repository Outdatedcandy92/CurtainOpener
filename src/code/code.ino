#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>
#include <Preferences.h>  // Add Preferences for persistent storage

// Wi-Fi credentials
const char* ssid = "ssid";
const char* password = "pass";

// Pins
const int EN_PIN = 5;
const int STEP_PIN = 6;
const int DIR_PIN = 7;
const int MS1_PIN = 8;
const int MS2_PIN = 9;

// Server
WebServer server(80);
Preferences prefs;  // Declare Preferences object

// Settings variables (defaults)
float stepsPer100mm = 500.0;
float mmPer1000Steps = 40.0;

// Jog flags
bool jogForward = false;
bool jogBackward = false;
unsigned long lastJogStepTime = 0;
const unsigned long jogStepIntervalMicros = 1000;

// Stepper move function
void moveStepper(int steps, bool direction) {
  digitalWrite(EN_PIN, LOW);
  digitalWrite(DIR_PIN, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(EN_PIN, HIGH);
}

// === Web UI ===
void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>Stepper Control</title>
    <style>
      body { font-family: Arial, sans-serif; max-width: 500px; margin: 20px auto; }
      h2 { text-align: center; }
      label, select, input, button { display: block; width: 100%; margin-top: 10px; font-size: 16px; }
      .status { margin-top: 15px; font-style: italic; color: green; }
      nav { text-align: center; margin-bottom: 20px; }
      nav a { margin: 0 10px; text-decoration: none; color: #007BFF; }
    </style>
  </head>
  <body>
    <h2>Stepper Control</h2>
    <nav><a href="/">Move</a> | <a href="/settings">Settings</a></nav>
    <form id="moveForm">
      <label for="moveValue">Distance (mm) or Steps:</label>
      <input type="number" id="moveValue" name="moveValue" step="any" required>
      <label for="unitSelect">Unit:</label>
      <select id="unitSelect" name="unitSelect">
        <option value="mm">Millimeters (mm)</option>
        <option value="steps">Steps</option>
      </select>
      <label for="directionSelect">Direction:</label>
      <select id="directionSelect" name="directionSelect">
        <option value="1">Forward</option>
        <option value="0">Backward</option>
      </select>
      <button type="submit">Move</button>
    </form>
    <div class="status" id="statusMsg"></div>
    <h3>Jog Controls (Hold to move)</h3>
    <button id="jogBackward">⬅ Hold to Move Backward</button>
    <button id="jogForward">Hold to Move Forward ➡</button>
    <script>
      const moveForm = document.getElementById('moveForm');
      const statusMsg = document.getElementById('statusMsg');
      moveForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        statusMsg.textContent = 'Moving...';
        const value = parseFloat(moveForm.moveValue.value);
        const unit = moveForm.unitSelect.value;
        const dir = moveForm.directionSelect.value;
        const url = unit === 'mm' ? '/move_mm' : '/move_steps';
        const params = new URLSearchParams();
        if(unit === 'mm') params.append('distance', value);
        else params.append('steps', value);
        params.append('dir', dir);
        try {
          const resp = await fetch(url + '?' + params.toString());
          const text = await resp.text();
          statusMsg.textContent = text;
        } catch (err) {
          statusMsg.textContent = 'Error: ' + err;
        }
      });

      function sendJog(dir, action) {
        fetch(`/jog?dir=${dir}&action=${action}`).catch(console.error);
      }

      const jogForwardBtn = document.getElementById('jogForward');
      const jogBackwardBtn = document.getElementById('jogBackward');
      ['mousedown','touchstart'].forEach(evt => {
        jogForwardBtn.addEventListener(evt, () => sendJog(1,1));
        jogBackwardBtn.addEventListener(evt, () => sendJog(0,1));
      });
      ['mouseup','mouseleave','touchend','touchcancel'].forEach(evt => {
        jogForwardBtn.addEventListener(evt, () => sendJog(1,0));
        jogBackwardBtn.addEventListener(evt, () => sendJog(0,0));
      });
    </script>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleSettings() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>Stepper Settings</title>
    <style>
      body { font-family: Arial, sans-serif; max-width: 400px; margin: 20px auto; }
      h2, nav { text-align: center; }
      label, input, button { display: block; width: 100%; margin-top: 10px; font-size: 16px; }
      .status { margin-top: 15px; font-style: italic; color: green; }
      nav a { margin: 0 10px; text-decoration: none; color: #007BFF; }
    </style>
  </head>
  <body>
    <h2>Stepper Settings</h2>
    <nav><a href="/">Move</a> | <a href="/settings">Settings</a></nav>
    <form id="settingsForm">
      <label for="stepsPer100mm">Steps per 100 mm:</label>
      <input type="number" id="stepsPer100mm" name="stepsPer100mm" step="any" value=")rawliteral" + String(stepsPer100mm, 2) + R"rawliteral(">
      <label for="mmPer1000Steps">or mm per 1000 steps:</label>
      <input type="number" id="mmPer1000Steps" name="mmPer1000Steps" step="any" value=")rawliteral" + String(mmPer1000Steps, 2) + R"rawliteral(">
      <button type="submit">Update Settings</button>
    </form>
    <div class="status" id="settingsStatus"></div>
    <script>
      const settingsForm = document.getElementById('settingsForm');
      const settingsStatus = document.getElementById('settingsStatus');
      settingsForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        const steps100 = parseFloat(settingsForm.stepsPer100mm.value);
        const mm1000 = parseFloat(settingsForm.mmPer1000Steps.value);
        if(steps100 > 0) {
          const newMmPer1000 = 100000.0 / steps100;
          const resp = await fetch(`/update_settings?stepsPer100mm=${steps100}&mmPer1000Steps=${newMmPer1000}`);
          const text = await resp.text();
          settingsStatus.textContent = text;
          settingsForm.mmPer1000Steps.value = newMmPer1000.toFixed(2);
        } else if (mm1000 > 0) {
          const newStepsPer100mm = 100000.0 / mm1000;
          const resp = await fetch(`/update_settings?stepsPer100mm=${newStepsPer100mm}&mmPer1000Steps=${mm1000}`);
          const text = await resp.text();
          settingsStatus.textContent = text;
          settingsForm.stepsPer100mm.value = newStepsPer100mm.toFixed(2);
        } else {
          settingsStatus.textContent = "Please enter valid positive values.";
        }
      });
    </script>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleUpdateSettings() {
  if (server.hasArg("stepsPer100mm") && server.hasArg("mmPer1000Steps")) {
    float newStepsPer100mm = server.arg("stepsPer100mm").toFloat();
    float newMmPer1000Steps = server.arg("mmPer1000Steps").toFloat();
    if (newStepsPer100mm > 0 && newMmPer1000Steps > 0) {
      stepsPer100mm = newStepsPer100mm;
      mmPer1000Steps = newMmPer1000Steps;

      prefs.begin("stepper", false); // write mode
      prefs.putFloat("steps100mm", stepsPer100mm);
      prefs.putFloat("mm1000steps", mmPer1000Steps);
      prefs.end();

      server.send(200, "text/plain", "Settings updated.");
      return;
    }
  }
  server.send(400, "text/plain", "Invalid parameters.");
}

void handleMoveMM() {
  if (server.hasArg("distance") && server.hasArg("dir")) {
    float distance = server.arg("distance").toFloat();
    bool dir = server.arg("dir").toInt();
    int steps = (distance * stepsPer100mm) / 100.0;
    moveStepper(steps, dir);
    server.send(200, "text/plain", "Moved " + String(distance, 2) + " mm (" + String(steps) + " steps)");
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void handleMoveSteps() {
  if (server.hasArg("steps") && server.hasArg("dir")) {
    int steps = server.arg("steps").toInt();
    bool dir = server.arg("dir").toInt();
    moveStepper(steps, dir);
    server.send(200, "text/plain", "Moved " + String(steps) + " steps");
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void handleJog() {
  if (server.hasArg("dir") && server.hasArg("action")) {
    int dir = server.arg("dir").toInt();
    bool action = server.arg("action").toInt();
    if (dir == 0) jogBackward = action;
    else if (dir == 1) jogForward = action;
    server.send(200, "text/plain", "Jog " + String(action ? "started" : "stopped"));
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(MS1_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);
  digitalWrite(MS1_PIN, LOW);
  digitalWrite(MS2_PIN, LOW);
  digitalWrite(EN_PIN, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  // Load settings
  prefs.begin("stepper", true);
  float savedSteps = prefs.getFloat("steps100mm", -1);
  float savedMM = prefs.getFloat("mm1000steps", -1);
  prefs.end();

  if (savedSteps > 0 && savedMM > 0) {
    stepsPer100mm = savedSteps;
    mmPer1000Steps = savedMM;
    Serial.println("Loaded saved settings.");
  } else {
    Serial.println("Using default settings.");
  }

  server.on("/", handleRoot);
  server.on("/settings", handleSettings);
  server.on("/update_settings", handleUpdateSettings);
  server.on("/move_mm", handleMoveMM);
  server.on("/move_steps", handleMoveSteps);
  server.on("/jog", handleJog);
  server.begin();

  ArduinoOTA.setHostname("ESP32C3-Stepper");
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();

  if (jogForward || jogBackward) {
    unsigned long now = micros();
    if (now - lastJogStepTime >= jogStepIntervalMicros) {
      digitalWrite(EN_PIN, LOW);
      digitalWrite(DIR_PIN, jogForward ? HIGH : LOW);
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP_PIN, LOW);
      lastJogStepTime = now;
    }
  } else {
    digitalWrite(EN_PIN, HIGH);
  }
}
