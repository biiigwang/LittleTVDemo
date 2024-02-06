#include <Arduino.h>

#include "utils.h"
#ifdef ESP_TFT_DEMO
#include "tft_espi_demo/tft_espi_demo.h"
tft_esp::TFT_eSPI_Demo tft_demo = tft_esp::TFT_eSPI_Demo();
#elif ESP_QR_DEMO || ESP_WIFI_MANAGER_DEMO
#include <TFT_eSPI.h>

#include <memory>

#include "esp_gen_qr_demo/esp_gen_qr_demo.h"
using namespace esp_gen_qr;
#define WIFI_SSID F("LittleTV")
#define WIFI_PASSWD F("00000000")
#endif

#ifdef ESP_WIFI_MANAGER_DEMO
#define FS_NO_GLOBALS
#include <FS.h>
using FS = fs::FS;
using File = fs::File;
using Dir = fs::Dir;

#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#endif

void setup(void) {
  Serial.begin(115200);
#ifdef ESP_TFT_DEMO
#elif ESP_QR_DEMO
  auto sp_tft = std::make_shared<TFT_eSPI>();
  // 初始化屏幕
  sp_tft->begin();
  auto espGenQrDemo = EspGenQrDemo(sp_tft);

  // 拼接Wi-Fi连接信息
  String qr_msg = (F("I Love You❤️!"));

  espGenQrDemo.ShowQrCode(qr_msg.c_str(), 20, 20, 200, 3);
#elif ESP_WIFI_MANAGER_DEMO
  auto sp_tft = std::make_shared<TFT_eSPI>();
  // 初始化屏幕
  sp_tft->begin();
  sp_tft->fillScreen(TFT_BLACK);
  sp_tft->setTextColor(TFT_WHITE);

  auto espGenQrDemo = EspGenQrDemo(sp_tft);

  // 拼接Wi-Fi连接信息
  String qr_msg = (F("WIFI:T:WPA;S:"));
  qr_msg += WIFI_SSID;
  qr_msg += F(";P:");
  qr_msg += WIFI_PASSWD;
  qr_msg += F(";H:;");

  // 0. 声明Wi-Fi Manager
  WiFiManager wifiManager;
  // 1. 设置Wi-Fi为STA模式
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
                        // it is a good practice to make sure your code sets
                        // wifi mode how you want it.

  // 2. 配置自动连接失败回调函数注册
  // 回调函数当设备在 WiFi 连接尝试失败后进入配置模式时执行
  wifiManager.setAPCallback([&](WiFiManager* wifimanager) {
    LOG_I_PRINTLN(F("Wi-Fi自动连接失败, 显示热点二维码"));
    // 连接失败时显示热点二维码
    espGenQrDemo.ShowQrCode(qr_msg.c_str(), 20, 20, 200, 3);
  });

  // 3. Wi-Fi成功连接，保存配置后回调函数注册
  wifiManager.setSaveConfigCallback([&]() {
    LOG_I_PRINTLN("Wi-Fi配置成功, 即将重启设备");
    delay(5000);
    ESP.reset();
  });
  LOG_I_PRINTLN("尝试自动重连Wi-Fi");
  wifiManager.autoConnect(String(WIFI_SSID).c_str(),
                          String(WIFI_PASSWD).c_str());

  sp_tft->setTextSize(3);
  sp_tft->setCursor(0, 5);
  sp_tft->println(F("IP:"));
  sp_tft->setCursor(0, 40);
  sp_tft->println(WiFi.localIP().toString());

  LOG_I_PRINTLN("Wi-Fi自动连接成功");
  Serial.println(F("\nInitialisation done."));
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP().toString());
#endif

  delay(1000);
}

void loop() {
#ifdef ESP_TFT_DEMO
  // tft测试
  // tft_demo.loop();
#endif
}