#include "MQTT_Manager.h"
#include "Config.h"

WiFiClient espClient;
PubSubClient mqtt(espClient);

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String cmd = "";
  for (int i = 0; i < length; i++) cmd += (char)payload[i];
  
  Serial.print("\n[MQTT DOWNLINK] Lenh: ");
  Serial.println(cmd);
  
  // Đẩy lệnh xuống UM980 qua Serial1
  Serial1.print(cmd);
  Serial1.print("\r\n");
}

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

void publishData(String payload) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[MQTT UPLINK] ");
    Serial.println(payload);
    mqtt.publish(TOPIC_PUB_DATA, payload.c_str());
  }
}

void publishHealth(String payload) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[MQTT HEALTH] ");
    Serial.println(payload);
    mqtt.publish(TOPIC_PUB_HEALTH, payload.c_str());
  }
}

void publishSensorData(String payload) {
  if (mqtt.connected() && payload.length() > 0) {
    Serial.print("[MQTT SENSOR] ");
    Serial.println(payload);
    mqtt.publish(TOPIC_PUB_SENSOR, payload.c_str());
  }
}

bool isMqttConnected() {
  return mqtt.connected();
}