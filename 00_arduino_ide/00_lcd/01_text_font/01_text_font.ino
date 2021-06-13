#include <M5Stack.h>

void setup() {
  M5.begin();

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("Font 1");
  M5.Lcd.setTextFont(2);  // Font変更、初期値は1
  M5.Lcd.println("Font 2");
}

void loop() {}