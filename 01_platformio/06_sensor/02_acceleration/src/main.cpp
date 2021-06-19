#define M5STACK_MPU6886

#include <ArduinoOSCWiFi.h>
#include <M5Stack.h>

#include "./config.h"
#include "./m5_imu.h"

M5Imu M5_IMU;

void setup() {
  M5.begin();
  M5_IMU.initialize();
  M5.Lcd.setTextSize(2);
  M5.Lcd.clear();
}

void loop() {
  M5_IMU.update();
  if (M5_IMU.wasMeasured()) {
    float acc_x, acc_y, acc_z;
    M5_IMU.getAccelData(&acc_x, &acc_y, &acc_z);

    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Acceleration:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", acc_x,
                  acc_y, acc_z);
    M5.Lcd.printf("Actual Frequency %4.1fHz", M5_IMU.getActualFreq());
  }
}