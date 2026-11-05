#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =================================================
// PIN DEFINITIONS
// =================================================

#define LDR_DO      34

#define RED_LED     25
#define GREEN_LED   26
#define BLUE_LED    33

#define BUZZER      32

// =================================================
// LCD
// =================================================

LiquidCrystal_I2C lcd(0x27, 16, 2);

// =================================================
// WIFI ACCESS POINT
// =================================================

const char* ssid = "Nothing";
const char* password = "12345678";

// =================================================
// WEB SERVER
// =================================================

WebServer server(80);

// =================================================
// VARIABLES
// =================================================

int ldrState = 0;

String systemStatus = "SYSTEM SECURE";
String laserStatus = "LASER DETECTED";
String buzzerStatus = "OFF";


// =================================================
// UPDATE HARDWARE DATA
// =================================================

void updateSystem() {

  ldrState = digitalRead(LDR_DO);

  /*
    LDR MODULE LOGIC

    LOW  = Laser detected
           System Secure

    HIGH = Laser blocked
           Intruder Alert
  */

  if (ldrState == LOW) {

    systemStatus = "SYSTEM SECURE";
    laserStatus = "LASER DETECTED";
    buzzerStatus = "OFF";

    // RGB LED
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    // Buzzer
    digitalWrite(BUZZER, LOW);

    // LCD
    lcd.setCursor(0, 0);
    lcd.print("LDR STATE: 0   ");

    lcd.setCursor(0, 1);
    lcd.print("SYSTEM SECURE   ");
  }

  else {

    systemStatus = "INTRUDER ALERT";
    laserStatus = "LASER BLOCKED";
    buzzerStatus = "ON";

    // RGB LED
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

    // Buzzer
    digitalWrite(BUZZER, HIGH);

    // LCD
    lcd.setCursor(0, 0);
    lcd.print("LDR STATE: 1   ");

    lcd.setCursor(0, 1);
    lcd.print("INTRUDER ALERT  ");
  }
}


// =================================================
// WEB PAGE (sent ONCE, static shell + JS polling)
// =================================================

void handleRoot() {

  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Laser Security System</title>
<style>
body {
  font-family: Arial, sans-serif;
  background: #202124;
  color: white;
  text-align: center;
  margin: 0;
}
.container {
  max-width: 600px;
  margin: 40px auto;
  padding: 25px;
  background: #303134;
  border-radius: 20px;
}
h1 {
  color: #00bfff;
}
.card {
  padding: 18px;
  margin: 15px 0;
  background: #3c4043;
  border-radius: 12px;
  font-size: 20px;
}
.status {
  font-size: 30px;
  font-weight: bold;
  padding: 20px;
  border-radius: 15px;
  transition: background 0.3s ease;
}
.secure { background: #1b5e20; }
.alert  { background: #b71c1c; }
</style>
</head>
<body>
<div class="container">
<h1>ESP32 LASER SECURITY</h1>

<div class="status" id="statusBox">Loading...</div>

<div class="card">
LDR DIGITAL STATE: <b id="ldrState">-</b>
</div>

<div class="card">
LASER STATUS: <b id="laserStatus">-</b>
</div>

<div class="card">
BUZZER: <b id="buzzerStatus">-</b>
</div>

<div class="card">
DATA UPDATE INTERVAL: <b>1 SECOND</b>
</div>

<div class="card" id="connInfo" style="font-size:14px;color:#9aa0a6;">
Connecting...
</div>

</div>

<script>
async function refreshData() {
  try {
    const res = await fetch('/data', { cache: "no-store" });
    if (!res.ok) throw new Error("bad response");
    const data = await res.json();

    document.getElementById('ldrState').innerText = data.ldrState;
    document.getElementById('laserStatus').innerText = data.laserStatus;
    document.getElementById('buzzerStatus').innerText = data.buzzerStatus;

    const statusBox = document.getElementById('statusBox');
    statusBox.innerText = data.systemStatus;
    statusBox.className = "status " + (data.ldrState == 0 ? "secure" : "alert");

    document.getElementById('connInfo').innerText = "Connected - last update OK";
  } catch (err) {
    document.getElementById('connInfo').innerText = "Connection lost, retrying...";
  }
}

refreshData();
setInterval(refreshData, 1000);
</script>

</body>
</html>
)rawliteral";

  server.sendHeader("Connection", "close");
  server.send(200, "text/html", page);
}


// =================================================
// LIGHTWEIGHT JSON DATA ENDPOINT (polled every 1s)
// =================================================

void handleData() {

  String json = "{";
  json += "\"ldrState\":" + String(ldrState) + ",";
  json += "\"systemStatus\":\"" + systemStatus + "\",";
  json += "\"laserStatus\":\"" + laserStatus + "\",";
  json += "\"buzzerStatus\":\"" + buzzerStatus + "\"";
  json += "}";

  server.sendHeader("Connection", "close");
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.send(200, "application/json", json);
}


// =================================================
// 404 HANDLER (avoids hanging on unknown requests)
// =================================================

void handleNotFound() {
  server.sendHeader("Connection", "close");
  server.send(404, "text/plain", "Not found");
}


// =================================================
// SETUP
// =================================================

void setup() {

  Serial.begin(115200);

  // ================= PINS =================

  pinMode(LDR_DO, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);


  // ================= INITIAL STATE =================

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(BUZZER, LOW);


  // ================= LCD =================

  Wire.begin(21, 22);

  lcd.init();

  lcd.backlight();

  digitalWrite(BLUE_LED, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("LASER SECURITY");

  lcd.setCursor(0, 1);
  lcd.print("SYSTEM STARTING");

  delay(2000);

  digitalWrite(BLUE_LED, LOW);

  lcd.clear();


  // ================= WIFI =================

  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 LASER SECURITY SYSTEM");
  Serial.println("==============================");

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.softAPIP());


  // ================= WEB SERVER =================

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("WEB SERVER STARTED");

  lcd.clear();
}


// =================================================
// LOOP
// =================================================

void loop() {

  // Handle web requests
  server.handleClient();

  // Fixed 1-second data update interval
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {

    previousMillis = currentMillis;

    updateSystem();
  }
}
