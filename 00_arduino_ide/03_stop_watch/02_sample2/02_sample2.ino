#include <M5Stack.h>

bool is_measuring = false;
float accumulate_sec = 0;
float last_measure_sec = 0;
float measure_sec = 0;
float start_sec = 0;

int center_x = 160;
int center_y = 120;

void setup() { M5.begin(); }

void buttonManagement() {
  if (is_measuring) {
    if (M5.BtnC.wasPressed()) {
      is_measuring = false;
      M5.Speaker.tone(3520, 20);
    } else {
      measure_sec = millis() / 1000.0 - start_sec + accumulate_sec;
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      measure_sec = 0;
      accumulate_sec = 0;
      M5.Lcd.clear();
      M5.Speaker.tone(3520, 20);
    }
    if (M5.BtnC.wasPressed()) {
      start_sec = millis() / 1000.0;
      accumulate_sec = measure_sec;
      is_measuring = true;
      M5.Speaker.tone(3520, 20);
    }
  }
}

void drawSecond() {
  int inside_rad = 105;
  int outside_rad = 110;
  float measure_min = measure_sec / 60;
  float last_measure_min = last_measure_sec / 60;
  if (fmod(measure_min, 1) < fmod(last_measure_min, 1)) {
    M5.lcd.fillEllipse(center_x, center_y, outside_rad + 1, outside_rad + 1,
                       BLACK);
  }
  float div = 120;
  float quantum = floor(fmod(measure_min, 1) * div) / div;
  float quantum_angle = quantum * 2 * M_PI - M_PI / 2.0;
  int x0 = inside_rad * cos(quantum_angle) + center_x;
  int x1 = outside_rad * cos(quantum_angle) + center_x;
  int y0 = inside_rad * sin(quantum_angle) + center_y;
  int y1 = outside_rad * sin(quantum_angle) + center_y;
  M5.Lcd.drawLine(x0, y0, x1, y1, WHITE);
}

void drawBelowSecond() {
  int inside_rad = 95;
  int outside_rad = 100;
  if (fmod(measure_sec, 1) < fmod(last_measure_sec, 1)) {
    M5.lcd.fillEllipse(center_x, center_y, outside_rad + 1, outside_rad + 1,
                       BLACK);
  }
  float div = 40;
  float quantum = floor(fmod(measure_sec, 1) * div) / div;
  float quantum_angle = quantum * 2 * M_PI - M_PI / 2.0;
  int x0 = inside_rad * cos(quantum_angle) + center_x;
  int x1 = outside_rad * cos(quantum_angle) + center_x;
  int y0 = inside_rad * sin(quantum_angle) + center_y;
  int y1 = outside_rad * sin(quantum_angle) + center_y;
  M5.Lcd.drawLine(x0, y0, x1, y1, WHITE);
}

void drawTimeCenter() {
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(String(measure_sec), center_x, center_y, 7);
}

void loop() {
  M5.update();
  buttonManagement();
  drawSecond();
  drawBelowSecond();
  drawTimeCenter();
  last_measure_sec = measure_sec;
  delay(2);
}
