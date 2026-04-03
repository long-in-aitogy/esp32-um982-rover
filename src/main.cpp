#include <Arduino.h>
#include "Config.h"
#include "MQTT_Manager.h"
#include "NTRIP_Handler.h"
#include "NMEA_Parser.h"
#include "DataStructs.h"
#include "Sim_handler.h"
#include "Wifi_handler.h"

#if CONNECT_USING_WIFI
#include "wifi_handler.h"
WiFiClient espClient;
#else
#include "Sim_handler.h"
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm        modem(debugger);
#else
TinyGsm        modem(Serial);
#endif
TinyGsmClient espClient(modem);
#endif

PubSubClient mqtt(espClient);

String nmeaBuffer = "";
String latestGGA = ""; // Lưu GGA gốc mới nhất cho NTRIP

// Toạ độ của mục tiêu, tạm thời để giá trị mẫu
String targetGGA = "$GNGGA,045151.00,2104.44183385,N,10546.62503715,E,1,28,0.7,22.4381,M,-28.2448,M,,*6C";

gga_data_struct ggaData;
gga_data_struct targetGgaData;
ksxt_data_struct ksxtData;

unsigned long lastHealthCheck = 0;
const unsigned long HEALTH_INTERVAL = 30000; // Gửi báo cáo sức khỏe mỗi 30 giây (30000 ms)

void sendDeviceHealth() {
  // 1. Lấy các thông số hệ thống
  unsigned long uptime_s = millis() / 1000;
  uint32_t freeHeap = ESP.getFreeHeap();
  int32_t rssi = WiFi.RSSI();
  bool mqttOk = isMqttConnected(mqtt);
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
  publishHealth(mqtt, String(healthPayload));
}

void setup() {
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n=========================================");
  Serial.println("     ESP32 GNSS GATEWAY KHOI DONG        ");
  Serial.println("=========================================");

  // Khởi tạo giao tiếp với UM980
  Serial1.begin(GNSS_BAUD, SERIAL_8N1, RX_GNSS, TX_GNSS);
  if (CONNECT_USING_WIFI) {
    Serial.println("[SETUP] Su dung ket noi WIFI");
    setupWiFi();
  } else {
    Serial.println("[SETUP] Su dung ket noi SIM/GSM");
    setupGSM(modem);
  }
  
  setupMQTT(mqtt);
  setupNTRIP();
  
  Serial.println("=========================================");
  Serial.println("        KHOI DONG HOAN TAT               ");
  Serial.println("=========================================\n");
}

void loop() {
  // 1. Duy trì kết nối mạng
  loopMQTT(mqtt);
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

    if (c == '\n') {
      nmeaBuffer.trim(); 
      
      // Bắt dòng tọa độ
      if (nmeaBuffer.startsWith("$GNGGA") || nmeaBuffer.startsWith("$GPGGA") || nmeaBuffer.startsWith("$KSXT")) {
        // Cập nhật tọa độ mới nhất để NTRIP dùng xác thực (Mode 3)
        latestGGA = nmeaBuffer; 
        
        // Đẩy lên MQTT
        if (nmeaBuffer.startsWith("$KSXT")) {
          publishRaw(mqtt, nmeaBuffer, false);
          bool parseOk = parseKSXT_toStruct(nmeaBuffer, ksxtData);
          String jsonPayload = "";
          if (parseOk) {
            jsonPayload = parseKSXT_toJSON(ksxtData);
          }
          publishData(mqtt, jsonPayload, false);
        }
        else {
          publishRaw(mqtt, nmeaBuffer, true);
          bool parseOk = parseGGA_toStruct(nmeaBuffer, ggaData);
          String jsonPayload = "";
          if (parseOk) {
            jsonPayload = parseGGA_toJSON(ggaData);
          }
          publishData(mqtt, jsonPayload, false);
        }
      } 
      // Bắt dòng phản hồi lệnh
      else if (nmeaBuffer.startsWith("$KSXT")) {

      }
      else if (nmeaBuffer.startsWith("#")) {
        Serial.print("[UM980 RESPONSE] ");
        Serial.println(nmeaBuffer);
      }
      
      nmeaBuffer = ""; // Xóa buffer đón dòng mới
    }
  }
}