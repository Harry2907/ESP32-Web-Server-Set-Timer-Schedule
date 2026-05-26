# ESP32 OTA Blink 💡

A minimal ESP32 project that blinks the onboard LED on **pin 2** and supports **Over-The-Air (OTA) firmware updates** via ElegantOTA — no USB cable needed after the first flash.

---

## Features

- Connects to WiFi on boot
- Blinks onboard LED (pin 2) every 500ms
- OTA firmware update via browser at `http://<ESP32_IP>/update`
- Non-blocking blink using `millis()` — OTA always stays responsive

---

## Hardware Required

| Component | Details |
|-----------|---------|
| ESP32 Dev Board | Any variant (ESP32, ESP32-S2, etc.) |
| USB Cable | For first flash only |
| WiFi Network | 2.4GHz |

---

## Libraries Required

Install these via Arduino Library Manager:

| Library | Purpose |
|---------|---------|
| `WebServer` | Built-in with ESP32 Arduino core |
| `ElegantOTA` | Browser-based OTA update UI |
| `WiFi` | Built-in with ESP32 Arduino core |

> ⚠️ Do **NOT** use `ESPAsyncWebServer` alongside `WebServer` — they conflict on HTTP method names (`HTTP_GET`, `HTTP_POST`, etc.).

---

## Board Setup

1. Install ESP32 board support in Arduino IDE:
   - Go to **File → Preferences**
   - Add this URL to Additional Board Manager URLs:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to **Tools → Board → Board Manager** → search `esp32` → install

2. Select your board: **Tools → Board → ESP32 Dev Module**

---

## Configuration

Edit these two lines in the sketch with your WiFi credentials:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

## Full Sketch

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>

const char* ssid     = "HARSHAL";
const char* password = "11223344";

WebServer server(80);

#define LED_PIN 2

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hi! I am ESP32.");
  });

  ElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  ElegantOTA.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}
```

---

## First Flash (USB)

1. Connect ESP32 via USB
2. Select the correct **Port** under Tools → Port
3. Click **Upload** (→)
4. Open **Serial Monitor** at `115200` baud
5. You'll see:
   ```
   WiFi Connected
   IP Address: 192.168.x.xx
   HTTP server started
   ```
6. Note the IP address — you'll need it for OTA

---

## OTA Update (Wireless)

After the first USB flash, all future updates can be done wirelessly:

### Step 1 — Export the .bin
- **Sketch → Export Compiled Binary**
- Find the `.bin` file in your sketch folder

### Step 2 — Open OTA page in browser
```
http://<YOUR_ESP32_IP>/update
```
Example:
```
http://192.168.1.45/update
```

### Step 3 — Upload
1. Select **Firmware**
2. Click **Choose File** → select the `.bin` file
3. Click **Update**
4. Wait for the success message ✅
5. ESP32 reboots automatically with the new firmware

> ⚠️ Your PC must be on the **same WiFi network** as the ESP32

---

## LED Behavior

| State | LED |
|-------|-----|
| Connecting to WiFi | OFF (static) |
| Connected + Running | Blinking every 500ms |
| During OTA upload | Continues blinking (non-blocking) |

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| Won't connect to WiFi | Check SSID/password, ensure 2.4GHz network |
| Can't reach `/update` page | Confirm PC is on same network, check IP in Serial Monitor |
| OTA upload fails | Make sure `.bin` is the correct firmware file, try re-exporting |
| Compile error: HTTP_GET conflict | Remove `ESPAsyncWebServer` and `AsyncTCP` includes |
| LED not blinking | Check pin 2 is not used by something else on your board variant |

---

## Project Structure

```
your_sketch/
├── your_sketch.ino        # Main sketch
└── your_sketch.ino.bin    # Exported binary for OTA (after export)
```

---

## License

MIT — free to use, modify, and distribute.
