#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>

#define CONNECT_USING_WIFI false

void setupMQTT(PubSubClient &mqttClient);
void loopMQTT(PubSubClient &mqttClient);
void publishData(PubSubClient &mqttClient, String payload, bool isGGA);
void publishRaw(PubSubClient &mqttClient, String payload, bool isGGA);
void publishHealth(PubSubClient &mqttClient, String payload); // Thêm hàm gửi thông tin sức khỏe
bool isMqttConnected(PubSubClient &mqttClient);             // Thêm hàm lấy trạng thái kết nối MQTT

#endif