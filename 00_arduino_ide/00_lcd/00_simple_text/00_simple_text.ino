#include <M5Stack.h>  // M5Stackライブラリを読み込む

void setup() {
  // setupの中は、最初に一度だけ処理される

  M5.begin();  // M5Stackライブラリの初期化

  M5.Lcd.setTextSize(2);           // テキストのサイズを指定
  M5.Lcd.setCursor(0, 10);         // カーソルの位置を指定
  M5.Lcd.println("Hello world.");  // 文字列を表示
}

void loop() {
  // loopの中は、setupの後に繰り返し処理される
}