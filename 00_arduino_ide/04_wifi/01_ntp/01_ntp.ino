#include <M5Stack.h>
#include <WiFi.h>

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String NTP_SERVER = "ntp.nict.jp";  // NTPサーバーのアドレス

const long GMT_OFFSET_SEC = 9 * 3600;  // +9hours
const int DAYLIGHT_OFFSET_SEC = 0;     // summer time offset

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

  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC,
             NTP_SERVER.c_str());  // 時刻を同期
}

void loop() {
  struct tm timeinfo;
  M5.Lcd.setCursor(0, 50);
  if (!getLocalTime(&timeinfo)) {
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(
      String(timeinfo.tm_year + 1900) + "/" + String(timeinfo.tm_mon + 1) +
      "/" + String(timeinfo.tm_mday) + " " + String(timeinfo.tm_hour) + ":" +
      String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec) + "   ");
  delay(10);
}