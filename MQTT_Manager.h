#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

void setupWiFi();
void setupMQTT();
void loopMQTT();
void publishData(String payload);
void publishHealth(String payload); // Thêm hàm gửi thông tin sức khỏe
void publishSensorData(String payload); // Hàm gửi dữ liệu từ cảm biến BT
bool isMqttConnected();             // Thêm hàm lấy trạng thái kết nối MQTT

#endif