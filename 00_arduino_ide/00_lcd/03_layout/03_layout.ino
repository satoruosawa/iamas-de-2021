#include <M5Stack.h>

void setup() {
  M5.begin();

  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextDatum(MC_DATUM);  // テキストの原点をMiddle centreに指定
  M5.Lcd.drawString("Center", 160, 120);
  // println関数だとレイアウトされないので、drawString関数を使う。
}

void loop() {
  // loopの中は、setupの後に繰り返し処理される
}