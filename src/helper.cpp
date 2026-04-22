#include "helper.h"

void sendDeviceHealth() {
  // 1. Lấy các thông số hệ thống
  unsigned long uptime_s = millis() / 1000;
  uint32_t freeHeap = ESP.getFreeHeap();

  #if CONNECT_USING_WIFI
    int32_t rssi = WiFi.RSSI();
    String connected_via = "WiFi";
  #endif
  #if CONNECT_USING_4G
    int32_t rssi = modem.getSignalQuality();
    String connected_via = "GSM";
  #endif
  
  bool mqttOk = isMqttConnected(mqtt);
  bool ntripOk = isNtripConnected();
  bool gnssOk = (latestGGA.length() > 10); // Nếu có chuỗi NMEA hợp lệ
  
  // 2. Đóng gói thành JSON
  char healthPayload[256];
  snprintf(healthPayload, sizeof(healthPayload), 
           "{\"uptime_s\":%lu,\"free_heap_bytes\":%u,\"connected_via\":\"%s\",\"rssi_dbm\":%d,\"mqtt_ok\":%s,\"ntrip_ok\":%s,\"gnss_data_ok\":%s}", 
           uptime_s, freeHeap, connected_via, rssi, 
           mqttOk ? "true" : "false", 
           ntripOk ? "true" : "false",
           gnssOk ? "true" : "false");
           
  // 3. Gửi lên Topic theo dõi
  publishHealth(mqtt, String(healthPayload));
}