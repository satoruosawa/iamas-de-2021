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

  M5.Lcd.setTextSize(1);
  delay(100);
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  delay(100);

  M5.Lcd.setTextSize(2);
  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();
  if (M5_IMU.wasMeasured()) {
    // OSC送信
    OscWiFi.update();
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/roll", M5_IMU.roll());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/pitch", M5_IMU.pitch());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/yaw", M5_IMU.yaw());

    // 前
    if (M5_IMU.roll() < -30) {
      M5.Lcd.fillTriangle(0, 0, 320, 0, 160, 120, WHITE);
    } else {
      M5.Lcd.fillTriangle(0, 0, 320, 0, 160, 120, BLACK);
    }
    // 後ろ
    if (M5_IMU.roll() > 30) {
      M5.Lcd.fillTriangle(0, 240, 160, 120, 320, 240, WHITE);
    } else {
      M5.Lcd.fillTriangle(0, 240, 160, 120, 320, 240, BLACK);
    }
    // 左
    if (M5_IMU.pitch() < -30) {
      M5.Lcd.fillTriangle(0, 0, 160, 120, 0, 240, WHITE);
    } else {
      M5.Lcd.fillTriangle(0, 0, 160, 120, 0, 240, BLACK);
    }
    // 右
    if (M5_IMU.pitch() > 30) {
      M5.Lcd.fillTriangle(320, 0, 320, 240, 160, 120, WHITE);
    } else {
      M5.Lcd.fillTriangle(320, 0, 320, 240, 160, 120, BLACK);
    }
  }
}