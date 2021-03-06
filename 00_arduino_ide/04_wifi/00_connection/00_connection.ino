#include <M5Stack.h>
#include <WiFi.h>

// Wi-Fiの設定
const String SSID = WIFI_SSID;  // 各自のSSIDに変更 "ssid"
const String PASSWORD = WIFI_PASSWORD;  // 各自のWiFiパスワードに変更 "password"

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  // WiFi へ接続開始
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.print("Connecting to the WiFi AP: " + SSID);
  while (WiFi.status() != WL_CONNECTED) {
    // 接続完了までループ
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  // 接続完了

  delay(3000);
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());  // localのIPアドレスを表示
}

void loop() {}
