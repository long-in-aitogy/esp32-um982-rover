#include "BT_Sensor_Manager.h"
#include "BluetoothSerial.h"
#include "MQTT_Manager.h"
#include "Config.h"

BluetoothSerial SerialBT;
bool btConnected = false;
uint8_t sensorAddress[6];

// Hàm phụ trợ parse MAC string từ Config.h thành mảng bytes
void parseMacAddress(const char* macStr, uint8_t* macBytes) {
  int values[6];
  if (6 == sscanf(macStr, "%x:%x:%x:%x:%x:%x", 
                  &values[0], &values[1], &values[2], 
                  &values[3], &values[4], &values[5])) {
    for (int i = 0; i < 6; ++i) {
      macBytes[i] = (uint8_t)values[i];
    }
  } else {
    Serial.println("[BT] Lỗi định dạng MAC Address trong Config.h");
  }
}

// Task chạy ở background trên Core 0 (để Core 1 chuyên cho Arduino loop loop() và WiFi)
void btTask(void *pvParameters) {
  Serial.println("[BT Task] Da khoi dong trên Core: " + String(xPortGetCoreID()));
  
  parseMacAddress(SENSOR_MAC_ADDRESS, sensorAddress);
  
  String btBuffer = "";

  while (true) {
    if (!btConnected) {
      Serial.print("[BT] Dang ket noi toi cam bien ");
      Serial.println(SENSOR_MAC_ADDRESS);
      
      // Hàm connect này sẽ bị block nếu không tìm thấy thiết bị, nên phải chạy trong rtos task
      btConnected = SerialBT.connect(sensorAddress);
      
      if (btConnected) {
        Serial.println("[BT] KET NOI THANH CONG!");
      } else {
        Serial.println("[BT] Ket noi that bai, thu lai sau 10s...");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
      }
    } else {
      // Nếu đã kết nối, đọc dữ liệu gửi về từ cảm biến
      while (SerialBT.available()) {
        char c = SerialBT.read();
        btBuffer += c;
        if (c == '\n') {
          btBuffer.trim();
          if (btBuffer.length() > 0) {
            // Gửi thẳng dữ liệu nhận được lên MQTT
            publishSensorData(btBuffer);
          }
          btBuffer = "";
        }
      }
      
      if (!SerialBT.connected(10)) { // Thử ping nhẹ để check kết nối (10ms timeout)
        Serial.println("[BT] MAT KET NOI VOI CAM BIEN!");
        btConnected = false;
      }
      
      // Delay ngắn nhường CPU cho các task khác
      vTaskDelay(10 / portTICK_PERIOD_MS); 
    }
  }
}

void setupBTSensor() {
  SerialBT.begin("ESP32_Gateway", true); // Bật BT mode Master
  Serial.println("[BT] Bluetooth Master khoi dong.");
  
  // Khởi tạo FreeRTOS task, phân bổ 4096 bytes stack, priority 1, chạy trên Core 0
  xTaskCreatePinnedToCore(
    btTask,          /* Task function. */
    "BT_Task",       /* name of task. */
    4096,            /* Stack size of task */
    NULL,            /* parameter of the task */
    1,               /* priority of the task */
    NULL,            /* Task handle to keep track of created task */
    0                /* pin task to core 0 */
  ); 
}

bool isBTSensorConnected() {
  return btConnected;
}
