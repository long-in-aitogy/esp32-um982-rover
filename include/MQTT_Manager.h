#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>

#define CONNECT_USING_WIFI false

void setupMQTT();
void loopMQTT();
void publishData(String payload, bool isGGA);
void publishRaw(String payload, bool isGGA);
void publishHealth(String payload); // Thêm hàm gửi thông tin sức khỏe
bool isMqttConnected();             // Thêm hàm lấy trạng thái kết nối MQTT

#endif