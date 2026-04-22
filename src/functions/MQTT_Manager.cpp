#include "functions/MQTT_Manager.h"
#include "Top_Lvl_Config.h"
#include "Prog_Config.h"

// ================= ĐỊNH NGHĨA CÁC ĐỐI TƯỢNG CẦN CHO KẾT NỐI =================
#if CONNECT_USING_WIFI
#include "hardware/Wifi_handler.h"
static WiFiClient espClient;
#endif
#if CONNECT_USING_4G
#include "hardware/Sim_handler.h"
extern TinyGsm modem;
static TinyGsmClient espClient(modem);
#endif

PubSubClient mqtt(espClient);

// ================= ĐỊNH NGHĨA HÀM =================

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String cmd = "";
  for (int i = 0; i < length; i++) cmd += (char)payload[i];
  
  Serial.print("\n[MQTT DOWNLINK] Lenh: ");
  Serial.println(cmd);
  
  // Đẩy lệnh xuống UM980 qua Serial1
  Serial1.print(cmd);
  Serial1.print("\r\n");
}

void setupMQTT() {
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(mqttCallback);
}

void loopMQTT() {
  if (!mqtt.connected()) {
    Serial.println("\n[MQTT] Dang ket noi Broker...");
    String clientId = "ESP32_GW_" + String(random(0xffff), HEX);
    if (mqtt.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("[MQTT] Da ket noi!");
      mqtt.subscribe(TOPIC_SUB_CMD);
    } else {
      Serial.print("[MQTT] Loi rc=");
      Serial.print(mqtt.state());
      Serial.println(" -> Thu lai sau 5s");
      delay(5000);
    }
  }
  mqtt.loop();
}

void publishData(String payload, bool isGGA) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[MQTT UPLINK] ");
    Serial.println(payload);
    if (isGGA)
      mqtt.publish(TOPIC_PUB_DATA_GGA, payload.c_str());
    else
      mqtt.publish(TOPIC_PUB_DATA_KSXT, payload.c_str());
  }
}

void publishRaw(String payload, bool isGGA) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[UM982 GNSS RAW DATA] ");
    Serial.println(payload);
    if (isGGA) {
      mqtt.publish(TOPIC_PUB_RAW_GGA, payload.c_str());
    } else {
      mqtt.publish(TOPIC_PUB_RAW_KSXT, payload.c_str());
    }
  }
}

void publishHealth(String payload) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[MQTT HEALTH] ");
    Serial.println(payload);
    mqtt.publish(TOPIC_PUB_HEALTH, payload.c_str());
  }
}

bool isMqttConnected() {
  return mqtt.connected();
}