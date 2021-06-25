#include "./ui.h"
void drawNav(int mode) {
  M5.Lcd.fillRect(0, 190, 320, 50, BLACK);
  M5.Lcd.setTextDatum(BC_DATUM);
  M5.Lcd.setTextSize(1);
  switch (mode) {
    case 0:
      M5.Lcd.setFreeFont(&FreeSansBold9pt7b);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.drawString("Gyro", 67, 225);
      M5.Lcd.setFreeFont(&FreeSans9pt7b);
      M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150));
      M5.Lcd.drawString("Mag", 160, 225);
      M5.Lcd.drawString("Cal", 253, 225);
      M5.Lcd.fillRect(37, 234, 60, 6, WHITE);
      break;
    case 1:
      M5.Lcd.setFreeFont(&FreeSansBold9pt7b);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.drawString("Mag", 160, 225);
      M5.Lcd.setFreeFont(&FreeSans9pt7b);
      M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150));
      M5.Lcd.drawString("Gyro", 67, 225);
      M5.Lcd.drawString("Cal", 253, 225);
      M5.Lcd.fillRect(130, 234, 60, 6, WHITE);
      break;
    case 2:
      M5.Lcd.setFreeFont(&FreeSansBold9pt7b);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.drawString("Cal", 253, 225);
      M5.Lcd.setFreeFont(&FreeSans9pt7b);
      M5.Lcd.setTextColor(M5.Lcd.color565(50, 50, 50));
      M5.Lcd.drawString("Gyro", 67, 225);
      M5.Lcd.drawString("Mag", 160, 225);
      M5.Lcd.fillRect(223, 234, 60, 6, WHITE);
      break;
    default:
      break;
  }
}

void drawUi(int mode) {
  switch (mode) {
    case 0:
      drawGyroUi();
      break;
    case 1:
      drawMagUi();
      break;
    default:
      break;
  }
}

void drawGyroUi() {
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150));
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.drawString("Sensing Data", 80, 10);
  M5.Lcd.drawString("State", 240, 10);
  M5.Lcd.drawLine(160, 10, 160, 190, M5.Lcd.color565(150, 150, 150));
  M5.Lcd.setTextDatum(TL_DATUM);
  M5.Lcd.drawString("X", 20, 40);
  M5.Lcd.drawString("Y", 20, 85);
  M5.Lcd.drawString("Z", 20, 130);
}

void drawMagUi() {
  M5.Lcd.fillRect(0, 0, 320, 190, BLACK);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150));
  M5.Lcd.setFreeFont(&FreeSans9pt7b);
  M5.Lcd.drawString("Sensing Data", 80, 10);
  M5.Lcd.drawString("Direction", 240, 10);
  M5.Lcd.drawLine(160, 10, 160, 190, M5.Lcd.color565(150, 150, 150));
  M5.Lcd.setTextDatum(TL_DATUM);
  M5.Lcd.drawString("X", 20, 40);
  M5.Lcd.drawString("Y", 20, 85);
  M5.Lcd.drawString("Z", 20, 130);
  drawCompassFrame();
}

void drawGyroValue(float gyro_x, float gyro_y, float gyro_z,
                   float gyro_offset_x, float gyro_offset_y,
                   float gyro_offset_z) {
  M5.Lcd.setTextDatum(TR_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setFreeFont(&FreeSansBold9pt7b);
  M5.Lcd.drawString("    " + String(gyro_x), 130, 40);
  M5.Lcd.drawString("    " + String(gyro_y), 130, 85);
  M5.Lcd.drawString("    " + String(gyro_z), 130, 130);
  M5.Lcd.setTextFont(1);
  M5.Lcd.drawString("(" + String(gyro_offset_x) + ")", 130, 62);
  M5.Lcd.drawString("(" + String(gyro_offset_y) + ")", 130, 107);
  M5.Lcd.drawString("(" + String(gyro_offset_z) + ")", 130, 152);
}

void drawMagValue(float mag_x, float mag_y, float mag_z, float mag_offset_x,
                  float mag_offset_y, float mag_offset_z) {
  M5.Lcd.setTextDatum(TR_DATUM);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setFreeFont(&FreeSansBold9pt7b);
  M5.Lcd.drawString("    " + String(mag_x), 130, 40);
  M5.Lcd.drawString("    " + String(mag_y), 130, 85);
  M5.Lcd.drawString("    " + String(mag_z), 130, 130);
  M5.Lcd.setTextFont(1);
  M5.Lcd.drawString("(" + String(mag_offset_x) + ")", 130, 62);
  M5.Lcd.drawString("(" + String(mag_offset_y) + ")", 130, 107);
  M5.Lcd.drawString("(" + String(mag_offset_z) + ")", 130, 152);
}

void drawCompassFrame() {
  int center_x = 240;
  int center_y = 95;
  for (int i = 0; i < 40; i++) {
    float angle = M_PI * 2.0 / 40 * i;
    int inner = 43;
    int outer = 45;
    if (i % 5 == 0) inner = 38;
    int x0 = inner * cos(angle) + center_x;
    int x1 = outer * cos(angle) + center_x;
    int y0 = inner * sin(angle) + center_y;
    int y1 = outer * sin(angle) + center_y;
    M5.Lcd.drawLine(x0, y0, x1, y1, M5.Lcd.color565(50, 50, 50));
  }
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(M5.Lcd.color565(150, 150, 150));
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextDatum(BC_DATUM);
  M5.Lcd.drawString("0", 241, 42);
  M5.Lcd.setTextDatum(MR_DATUM);
  M5.Lcd.drawString("90", 187, 95);
  M5.Lcd.setTextDatum(ML_DATUM);
  M5.Lcd.drawString("-90", 293, 95);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.drawString("180,-180", 240, 148);
}

void drawCompassNeedle(float angle) {
  int center_x = 240;
  int center_y = 95;
  int x = 35 * cos((-angle - 90.0) / 180.0 * M_PI) + center_x;
  int y = 35 * sin((-angle - 90.0) / 180.0 * M_PI) + center_y;
  M5.Lcd.fillEllipse(center_x, center_y, 36, 36, BLACK);
  M5.Lcd.drawLine(center_x, center_y, x, y, RED);
}
