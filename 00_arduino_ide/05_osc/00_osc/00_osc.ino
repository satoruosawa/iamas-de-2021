#include <ArduinoOSCWiFi.h>
#include <M5Stack.h>

// Wi-Fiの設定
const String SSID = WIFI_SSID;          // 各自のSSIDに変更 "ssid"
const String PASSWORD = WIFI_PASSWORD;  // 各自のWiFiパスワードに変更 "pass"

// OSCの設定
const String TARGEET_IP = PC_IP_ADDRESS;  // macのIPアドレスに変更 "0.0.0.0"
const int TARGET_PORT = 10000;            // 受け取り側のポート

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  // WiFi へ接続開始
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.print("Connecting to the WiFi AP: " + SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  // 接続完了

  delay(3000);
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());
}

void loop() {
  OscWiFi.update();  // OSCを使うときは、この行を追加
  float second = millis() / 1000.0;  // ミリ秒から秒に変換
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/time",
               second);  // OSCデータを送信

  // LCD 表示
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.print("Value: ");
  M5.Lcd.println(second);

  delay(10);
}
