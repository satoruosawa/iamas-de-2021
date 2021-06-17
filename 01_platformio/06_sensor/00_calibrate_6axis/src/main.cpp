#define M5STACK_MPU6886

#include <M5Stack.h>
#include <Preferences.h>

Preferences PREFS;

float GYRO_X_OFFSET = 0;
float GYRO_Y_OFFSET = 0;
float GYRO_Z_OFFSET = 0;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  PREFS.begin("mpu6886", true);
  GYRO_X_OFFSET = PREFS.getFloat("x", 0);
  GYRO_Y_OFFSET = PREFS.getFloat("y", 0);
  GYRO_Z_OFFSET = PREFS.getFloat("z", 0);
  PREFS.end();

  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.update();
  float gyro_x;  // X軸方向のジャイロデータを受け取るための変数
  float gyro_y;  // Y軸方向のジャイロデータを受け取るための変数
  float gyro_z;  // Z軸方向のジャイロデータを受け取るための変数

  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);  // ジャイロデータを取得

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("X:%7.2f[deg/s]\nY:%7.2f[deg/s]\nZ:%7.2f[deg/s]",
                gyro_x + GYRO_X_OFFSET, gyro_y + GYRO_Y_OFFSET,
                gyro_z + GYRO_Z_OFFSET);
  M5.Lcd.setCursor(0, 120);
  M5.Lcd.printf("OFFSET\n");
  M5.Lcd.printf("X:%7.2f[deg/s]\nY:%7.2f[deg/s]\nZ:%7.2f[deg/s]", GYRO_X_OFFSET,
                GYRO_Y_OFFSET, GYRO_Z_OFFSET);

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
    M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);  // ジャイロデータを取得
    GYRO_X_OFFSET = -gyro_x;
    GYRO_Y_OFFSET = -gyro_y;
    GYRO_Z_OFFSET = -gyro_z;
    PREFS.begin("mpu6886", false);
    PREFS.putFloat("x", GYRO_X_OFFSET);
    PREFS.putFloat("y", GYRO_Y_OFFSET);
    PREFS.putFloat("z", GYRO_Z_OFFSET);
    PREFS.end();
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("DONE CALIBRATION", 160, 120);
    delay(1000);
    M5.Lcd.clear();
  }

  delay(1);
}