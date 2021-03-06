#define M5STACK_MPU6886

#include <ArduinoOSCWiFi.h>
#include <M5Stack.h>

#include "./m5_imu.h"

M5Imu M5_IMU;

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

void setup() {
  M5.begin();
  M5_IMU.initialize(20);

  M5.Lcd.setTextSize(2);
  delay(100);
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.print("Connecting to the WiFi AP: " + SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  delay(1000);

  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();
  if (M5_IMU.wasMeasured()) {
    // OSC送信
    OscWiFi.update();
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/acceleration",
                 M5_IMU.accX(), M5_IMU.accY(), M5_IMU.accZ());
    if (M5_IMU.accZ() > 1.2) {
      M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
    } else {
      M5.Lcd.fillRect(0, 0, 320, 240, BLACK);
    }
  }
}