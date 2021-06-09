#include <M5Stack.h>

bool flag = false;

void setup() { M5.begin(); }

void loop() {
  if (flag) {
    M5.Lcd.fillRect(90, 50, 140, 140, BLUE);
  } else {
    M5.Lcd.fillRect(90, 50, 140, 140, RED);
  }
  flag = !flag;
  delay(1000);
}
