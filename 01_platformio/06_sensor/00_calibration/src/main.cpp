#include <M5Stack.h>

#include "./m5_imu.h"  // 磁気センサーライブラリを使うための宣言

M5Imu M5_IMU;  // センサーライブラリを使うための定義

void setup() {
  M5.begin();
  M5_IMU.initialize();  // センサーライブラリの初期化
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.update();      // ボタンを使うので必要
  M5_IMU.update();  // センサーデータの更新
  if (M5_IMU.wasMeasured()) {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", M5_IMU.gyroX(),
                  M5_IMU.gyroY(), M5_IMU.gyroZ());
    M5.Lcd.printf("Magnetic Field:\n  X: %5.2f\n  Y: %5.2f\n  Z: %5.2f\n",
                  M5_IMU.magX(), M5_IMU.magY(), M5_IMU.magZ());
    M5.Lcd.printf("Direction: %7.2f[deg]", M5_IMU.headDirection());

    // M5.Lcd.setCursor(0, 180);
    // M5.Lcd.print("Press Button A to start \ncalibration.");
  }
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.clear();
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.setTextSize(4);
    M5.Lcd.drawString("3", 160, 120);
    delay(1000);
    M5.Lcd.drawString("2", 160, 120);
    delay(1000);
    M5.Lcd.drawString("1", 160, 120);
    delay(1000);
    M5.update();
    M5_IMU.calibrateMpu6886();
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("DONE CALIBRATION", 160, 120);
    delay(1000);
    M5.Lcd.clear();
  } else if (M5.BtnC.wasPressed()) {
    M5.Lcd.setTextSize(2);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Flip + rotate M5Stack GREY");
    M5_IMU.calibrateBmm150(20000);  // 20秒間キャリブレーション
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Done calibration.");
    delay(1000);
    M5.Lcd.clear(BLACK);
  }
  delay(100);
}