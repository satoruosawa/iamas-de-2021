#include <M5Stack.h>

int number = 0;  // int型のnumberという名前の変数を宣言して、初期値0を代入

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(4);
}

void loop() {
  M5.Lcd.setCursor(150, 100);
  M5.Lcd.println(number);
  number = number + 1;  // numberに1追加して代入
  delay(1000);          // 1000ミリ秒 = 1秒間 待つ
}
