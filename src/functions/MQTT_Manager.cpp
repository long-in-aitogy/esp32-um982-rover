#include "functions/MQTT_Manager.h"
#include "Top_Lvl_Config.h"
#include "Prog_Config.h"

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

void setupMQTT(PubSubClient &mqttClient) {
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
}

void loopMQTT(PubSubClient &mqttClient) {
  if (!mqttClient.connected()) {
    Serial.println("\n[MQTT] Dang ket noi Broker...");
    String clientId = "ESP32_GW_" + String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("[MQTT] Da ket noi!");
      mqttClient.subscribe(TOPIC_SUB_CMD);
    } else {
      Serial.print("[MQTT] Loi rc=");
      Serial.print(mqttClient.state());
      Serial.println(" -> Thu lai sau 5s");
      delay(5000);
    }
  }
  mqttClient.loop();
}

void publishData(PubSubClient &mqttClient, String payload, bool isGGA) {
  if (mqttClient.connected() && payload.length() > 0) {
    Serial.print("[MQTT UPLINK] ");
    Serial.println(payload);
    if (isGGA)
      mqttClient.publish(TOPIC_PUB_DATA_GGA, payload.c_str());
    else
      mqttClient.publish(TOPIC_PUB_DATA_KSXT, payload.c_str());
  }
}

void publishRaw(PubSubClient &mqttClient, String payload, bool isGGA) {
  if (mqttClient.connected() && payload.length() > 0) {
    Serial.print("[UM982 GNSS RAW DATA] ");
    Serial.println(payload);
    if (isGGA) {
      mqttClient.publish(TOPIC_PUB_RAW_GGA, payload.c_str());
    } else {
      mqttClient.publish(TOPIC_PUB_RAW_KSXT, payload.c_str());
    }
  }
}

void publishHealth(PubSubClient &mqttClient, String payload) {
  if (mqttClient.connected() && payload.length() > 0) {
    Serial.print("[MQTT HEALTH] ");
    Serial.println(payload);
    mqttClient.publish(TOPIC_PUB_HEALTH, payload.c_str());
  }
}

bool isMqttConnected(PubSubClient &mqttClient) {
  return mqttClient.connected();
}