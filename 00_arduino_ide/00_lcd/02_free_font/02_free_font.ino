#include <M5Stack.h>

void setup() {
  M5.begin();

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setFreeFont(&FreeMono9pt7b);  // Font変更
  M5.Lcd.println("Free Mono 9pt");
}

void loop() {
  // loopの中は、setupの後に繰り返し処理される
}