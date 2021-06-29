#define M5STACK_MPU6886  // MPU6886というセンサーを使うことを宣言

#include <M5Stack.h>

#include "./m5_imu.h"  // センサーライブラリを使うための宣言

M5Imu M5_IMU;  // センサーライブラリを使うための定義

void setup() {
  M5.begin();
  M5_IMU.initialize();  // センサーライブラリの初期化、M5.begin()の直後に行う
  M5.Lcd.setTextSize(2);
  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();             // センサーライブラリの更新
  if (M5_IMU.wasMeasured()) {  // 20Hzでセンサーデータを読み取る
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Acceleration");
    M5.Lcd.print("X: ");
    M5.Lcd.print(M5_IMU.accX());
    M5.Lcd.print("   \nY: ");
    M5.Lcd.print(M5_IMU.accY());
    M5.Lcd.print("   \nZ: ");
    M5.Lcd.print(M5_IMU.accZ());
    M5.Lcd.println("   ");
    // Serial.print(M5_IMU.accX());
    // Serial.print(",");
    // Serial.print(M5_IMU.accY());
    // Serial.print(",");
    // Serial.println(M5_IMU.accZ());
  }
}