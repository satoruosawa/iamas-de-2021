#include <M5Stack.h>

int x = 0;
int y = 0;

void setup() { M5.begin(); }

void loop() {
  M5.Lcd.fillRect(x, y, 18, 18, WHITE);

  x = x + 20;      // ループごとにxに20を追加する
  if (x >= 320) {  // 折り返し処理
    x = 0;
    y = y + 20;
  }

  delay(100);
}
