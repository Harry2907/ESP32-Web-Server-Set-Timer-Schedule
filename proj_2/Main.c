#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>      // Use this directly instead of ESPAsyncWebServer
#include <ElegantOTA.h>

const char* ssid     = "HARSHAL";
const char* password = "11223344";

WebServer server(80);

void setup() {
  Serial.begin(115200);
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

  // WebServer handlers take NO arguments — use the global `server` object inside
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hi! I am ESP32.");
  });

  ElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();      // Required for WebServer — don't leave this empty!
  ElegantOTA.loop();          // Required for ElegantOTA to process OTA events
}