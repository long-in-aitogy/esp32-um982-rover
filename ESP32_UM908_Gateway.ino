#include <Arduino.h>
#include "Config.h"
#include "MQTT_Manager.h"
#include "NTRIP_Handler.h"
#include "NMEA_Parser.h"

String nmeaBuffer = "";
String latestGGA = ""; // Lưu GGA gốc mới nhất cho NTRIP

unsigned long lastHealthCheck = 0;
const unsigned long HEALTH_INTERVAL = 30000; // Gửi báo cáo sức khỏe mỗi 30 giây (30000 ms)

void sendDeviceHealth() {
  // 1. Lấy các thông số hệ thống
  unsigned long uptime_s = millis() / 1000;
  uint32_t freeHeap = ESP.getFreeHeap();
  int32_t rssi = WiFi.RSSI();
  bool mqttOk = isMqttConnected();
  bool ntripOk = isNtripConnected();
  bool gnssOk = (latestGGA.length() > 10); // Nếu có chuỗi NMEA hợp lệ
  
  // 2. Đóng gói thành JSON
  char healthPayload[256];
  snprintf(healthPayload, sizeof(healthPayload), 
           "{\"uptime_s\":%lu,\"free_heap_bytes\":%u,\"wifi_rssi_dbm\":%d,\"mqtt_ok\":%s,\"ntrip_ok\":%s,\"gnss_data_ok\":%s}", 
           uptime_s, freeHeap, rssi, 
           mqttOk ? "true" : "false", 
           ntripOk ? "true" : "false",
           gnssOk ? "true" : "false");
           
  // 3. Gửi lên Topic theo dõi
  publishHealth(String(healthPayload));
}

void setup() {
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n=========================================");
  Serial.println("     ESP32 GNSS GATEWAY KHOI DONG        ");
  Serial.println("=========================================");

  // Khởi tạo giao tiếp với UM980
  Serial1.begin(GNSS_BAUD, SERIAL_8N1, RX_GNSS, TX_GNSS);
  
  setupWiFi();
  setupMQTT();
  setupNTRIP();
  
  Serial.println("=========================================");
  Serial.println("        KHOI DONG HOAN TAT               ");
  Serial.println("=========================================\n");
}

void loop() {
  // 1. Duy trì kết nối mạng
  loopMQTT();
  loopNTRIP(latestGGA);

  // === KIỂM TRA VÀ GỬI THÔNG TIN SỨC KHỎE ===
  if (millis() - lastHealthCheck >= HEALTH_INTERVAL) {
    sendDeviceHealth();
    lastHealthCheck = millis();
  }

  // 2. Xử lý luồng dữ liệu từ UM980
  while (Serial1.available()) {
    char c = Serial1.read();
    nmeaBuffer += c;
    if (c == '\n' || c == 0) {
      Serial.print("[UM982 GNSS INPUT DEBUG]"); // debug only
      Serial.println(nmeaBuffer);
    }

    if (c == '\n') {
      nmeaBuffer.trim(); 
      
      // Bắt dòng tọa độ
      if (nmeaBuffer.startsWith("$GNGGA") || nmeaBuffer.startsWith("$GPGGA")) {
        // Cập nhật tọa độ mới nhất để NTRIP dùng xác thực (Mode 3)
        latestGGA = nmeaBuffer; 

        // Đẩy dữ liệu chưa xử lý lên MQTT
        publishRaw(nmeaBuffer);
        
        // Giải mã thành JSON
        String jsonPayload = parseGGA_toJSON(nmeaBuffer);
        
        // Đẩy lên MQTT
        publishData(jsonPayload);
      } 
      // Bắt dòng phản hồi lệnh
      else if (nmeaBuffer.startsWith("#")) {
        Serial.print("[UM980 RESPONSE] ");
        Serial.println(nmeaBuffer);
      }
      
      nmeaBuffer = ""; // Xóa buffer đón dòng mới
    }
  }
}