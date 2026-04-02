#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>

#define CONNECT_USING_WIFI true

#if CONNECT_USING_WIFI
#include "wifi_handler.h"
#else
#include "Sim_handler.h"
#endif

void setupWiFi();
void setupMQTT();
void loopMQTT();
void publishData(String payload, bool isGGA);
void publishRaw(String payload, bool isGGA);
void publishHealth(String payload); // Thêm hàm gửi thông tin sức khỏe
bool isMqttConnected();             // Thêm hàm lấy trạng thái kết nối MQTT

#endif