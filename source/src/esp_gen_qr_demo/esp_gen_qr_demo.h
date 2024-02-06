#ifndef ESP_GEN_QR_DEMO_H
#define ESP_GEN_QR_DEMO_H
#include <ESP_QRcode.h>
#include <TFT_eSPI.h>

#include <memory>
namespace esp_gen_qr {
class EspGenQrDemo {
 private:
  /* data */
  /// TFT_eSPI类智能指针
  std::shared_ptr<TFT_eSPI> m_sp_tft;

  std::shared_ptr<ESP_QRcode> m_sp_qr;

 public:
  EspGenQrDemo(std::shared_ptr<TFT_eSPI> sp_tft);

  void ShowQrCode(const char* string, const int& x, const int& y,
                  const int& width, const int& version);

  ~EspGenQrDemo();
};

}  // namespace esp_gen_qr

#endif  // ESP_GEN_QR_DEMO_H
