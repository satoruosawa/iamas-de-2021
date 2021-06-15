#include <M5Stack.h>

void setup() { M5.begin(); }

void loop() {
  M5.update();  // ボタンかスピーカーを使うときは、この行を追加
  if (M5.BtnA.wasPressed()) {
    M5.Speaker.tone(3135, 40);  // 3135Hzの音を40ミリ秒再生
  }
  if (M5.BtnB.wasPressed()) {
    M5.Speaker.tone(3520, 40);  // 3520Hzの音を40ミリ秒再生
  }
  if (M5.BtnC.wasPressed()) {
    M5.Speaker.tone(3951, 40);  // 3951Hzの音を40ミリ秒再生
  }
}
