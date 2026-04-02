#include "wifi_handler.h"

void setupWiFi() {
  Serial.print("\n[WIFI] Dang ket noi mang: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
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
