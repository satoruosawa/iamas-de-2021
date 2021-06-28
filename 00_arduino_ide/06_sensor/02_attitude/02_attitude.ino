#define M5STACK_MPU6886

#include <M5Stack.h>

#include "./m5_imu.h"  // センサーライブラリを使うための宣言

M5Imu M5_IMU;  // センサーライブラリを使うための定義

void setup() {
  M5.begin();
  M5_IMU.initialize();  // センサーライブラリの初期化
  M5.Lcd.setTextSize(2);
  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();
  if (M5_IMU.wasMeasured()) {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Atitude");
    M5.Lcd.print("Roll: ");
    M5.Lcd.print(M5_IMU.roll());
    M5.Lcd.print("   \nPitch: ");
    M5.Lcd.print(M5_IMU.pitch());
    M5.Lcd.print("   \nYaw: ");
    M5.Lcd.print(M5_IMU.yaw());
    M5.Lcd.print("   \nSample Freq.: ");
    M5.Lcd.print(M5_IMU.actualSampleFrequency());
    M5.Lcd.println("Hz   ");
  }
}