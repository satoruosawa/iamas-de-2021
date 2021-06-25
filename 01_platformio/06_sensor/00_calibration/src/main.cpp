#include <M5Stack.h>

#include "./m5_imu.h"  // 磁気センサーライブラリを使うための宣言
#include "./ui.h"

M5Imu M5_IMU;  // センサーライブラリを使うための定義
int MODE = 0;  // 0:gyro,1:mag,2:cal

void setup() {
  M5.begin();
  M5_IMU.initialize();  // センサーライブラリの初期化
  drawNav(MODE);
  drawUi(MODE);
}

void drawGyro() {
  float gyro_offset_x, gyro_offset_y, gyro_offset_z;
  M5_IMU.getGyroOffsetData(&gyro_offset_x, &gyro_offset_y, &gyro_offset_z);
  drawGyroValue(M5_IMU.gyroX(), M5_IMU.gyroY(), M5_IMU.gyroZ(), gyro_offset_x,
                gyro_offset_y, gyro_offset_z);
  float gyro_max = max(abs(M5_IMU.gyroX()), abs(M5_IMU.gyroY()));
  gyro_max = max(gyro_max, abs(M5_IMU.gyroZ()));
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setFreeFont(&FreeSansBold12pt7b);
  if (gyro_max < 5) {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.drawString("      STAY      ", 240, 90);
  } else {
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.drawString("  ROTATING  ", 238, 90);
  }
}

void drawMag() {
  float mag_offset_x, mag_offset_y, mag_offset_z;
  M5_IMU.getMagOffsetData(&mag_offset_x, &mag_offset_y, &mag_offset_z);
  drawMagValue(M5_IMU.magX(), M5_IMU.magY(), M5_IMU.magZ(), mag_offset_x,
               mag_offset_y, mag_offset_z);
  drawCompassNeedle(M5_IMU.headDirection());
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.drawString("   " + String(int(M5_IMU.headDirection())) + "   ", 240,
                    170);
}

void calibrateGyro() {
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150), BLACK);
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.drawString("Put the M5Stack on the table.", 160, 80);
  M5.Lcd.setFreeFont(&FreeSans12pt7b);
  M5.Lcd.drawString(" 5 ", 160, 110);
  delay(1000);
  M5.Lcd.drawString(" 4 ", 160, 110);
  delay(1000);
  M5.Lcd.drawString(" 3 ", 160, 110);
  delay(1000);
  M5.Lcd.drawString(" 2 ", 160, 110);
  delay(1000);
  M5.Lcd.drawString(" 1 ", 160, 110);
  delay(1000);
  M5_IMU.calibrateMpu6886();
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.drawString("DONE CALIBRATION", 160, 80);
  delay(3000);
}

void calibrateMag() {
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150), BLACK);
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.drawString("Flip + rotate M5Stack for 30sec.", 160, 80);
  M5_IMU.calibrateBmm150(30000);  // 30秒間キャリブレーション
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.drawString("DONE CALIBRATION", 160, 80);
  delay(3000);
}

void loop() {
  M5.update();      // ボタンを使うので必要
  M5_IMU.update();  // センサーデータの更新
  if (M5_IMU.wasMeasured()) {
    switch (MODE) {
      case 0:
        drawGyro();
        break;
      case 1:
        drawMag();
        break;
      default:
        break;
    }
  }

  if (M5.BtnA.wasPressed()) {
    MODE = 0;
    drawNav(MODE);
    drawGyroUi();
  } else if (M5.BtnB.wasPressed()) {
    MODE = 1;
    drawNav(MODE);
    drawMagUi();
  } else if (M5.BtnC.wasPressed()) {
    drawNav(2);
    M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
    switch (MODE) {
      case 0:
        calibrateGyro();
        break;
      case 1:
        calibrateMag();
        break;
      default:
        break;
    }
    drawNav(MODE);
    drawUi(MODE);
  }
  delay(100);
}