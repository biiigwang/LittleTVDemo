#include "esp_gen_qr_demo.h"

#include <string>
using namespace esp_gen_qr;

EspGenQrDemo::EspGenQrDemo(std::shared_ptr<TFT_eSPI> sp_tft)
    : m_sp_tft(sp_tft), m_sp_qr(std::make_shared<ESP_QRcode>(sp_tft.get())) {}

EspGenQrDemo::~EspGenQrDemo() {}

void EspGenQrDemo::ShowQrCode(const char * string, const int& x,
                              const int& y, const int& width,
                              const int& version) {
  m_sp_tft->fillScreen(TFT_BLACK);
  m_sp_tft->setTextColor(TFT_RED, TFT_WHITE);
  // 内容 x坐标 y坐标 宽度 二维码版本
  m_sp_qr->qrcode(string, x, y, width, version);
}
