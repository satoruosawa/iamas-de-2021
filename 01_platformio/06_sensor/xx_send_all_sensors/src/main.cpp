#define M5STACK_MPU6886

#include <ArduinoOSCWiFi.h>
#include <M5Stack.h>

#include "./config.h"
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

  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();
  if (M5_IMU.wasMeasured()) {
    // OSC送信
    OscWiFi.update();
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/acceleration",
                 M5_IMU.accX(), M5_IMU.accY(), M5_IMU.accZ());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/gyro", M5_IMU.gyroX(),
                 M5_IMU.gyroY(), M5_IMU.gyroZ());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/magnetic_field",
                 M5_IMU.magX(), M5_IMU.magY(), M5_IMU.magZ());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/direction",
                 M5_IMU.headDirection());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/roll", M5_IMU.roll());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/pitch", M5_IMU.pitch());
    OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/yaw", M5_IMU.yaw());

    // LCD表示
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Send OSC");
    M5.Lcd.print("Target IP: ");
    M5.Lcd.print(TARGEET_IP.c_str());
    M5.Lcd.print(":");
    M5.Lcd.println(TARGET_PORT);
    M5.Lcd.println();
    M5.Lcd.printf("Acceleration:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n",
                  M5_IMU.accX(), M5_IMU.accY(), M5_IMU.accZ());
    M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", M5_IMU.gyroX(),
                  M5_IMU.gyroY(), M5_IMU.gyroZ());
    M5.Lcd.printf("Magnetic Field:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n",
                  M5_IMU.magX(), M5_IMU.magY(), M5_IMU.magZ());
    M5.Lcd.printf("direction: %7.2f\n", M5_IMU.headDirection());
    M5.Lcd.printf("Rotaion:\n   Roll: %7.2f\n  Pitch: %7.2f\n    Yaw: %7.2f\n",
                  M5_IMU.roll(), M5_IMU.pitch(), M5_IMU.yaw());
    M5.Lcd.printf("Actual Frequency %4.1fHz", M5_IMU.actualSampleRate());
  }
}