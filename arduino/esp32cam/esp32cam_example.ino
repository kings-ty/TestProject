#include <Arduino.h>
#include <esp32cam.h>
#include <WiFi.h>

const char* WIFI_SSID = "your_wifi_ssid";
const char* WIFI_PASS = "your_wifi_password";

void setup() {
  Serial.begin(115200);

  auto cfg = esp32cam::Camera::config();
  cfg.setPins(esp32cam::pins::AiThinker);
  cfg.setResolution(esp32cam::Resolution::find(640, 480));
  cfg.setBufferCount(1);

  if (!esp32cam::Camera.begin(cfg)) {
    Serial.println("Camera init failed");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  auto frame = esp32cam::capture();
  if (frame) {
    Serial.printf("Captured frame: %dx%d, %d bytes\n", frame->getWidth(), frame->getHeight(), frame->size());
    frame->release();
  } else {
    Serial.println("Capture failed");
  }
  delay(5000);
}
