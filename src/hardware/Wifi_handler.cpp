#include "hardware/Wifi_handler.h"

void setupWiFi(char* wifi_ssid, char* wifi_pass) {
  Serial.print("\n[WIFI] Dang ket noi mang: ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_pass);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++attempt > 30) {
      Serial.println("\n[ERROR] Ket noi WiFi that bai!");
      attempt = 0;
    }
  }
  Serial.println("\n[WIFI] Ket noi THANH CONG! IP: " + WiFi.localIP().toString());
}
