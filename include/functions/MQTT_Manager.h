#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

// ============ GẮN CÁC THƯ VIỆN CẦN THIẾT ==============

#include <Arduino.h>
#include <PubSubClient.h>
#include "Top_Lvl_Config.h"

extern PubSubClient mqtt;

// ================= KHAI BÁO HÀM =================

void setupMQTT();
void loopMQTT();
void publishData(String payload, bool isGGA);
void publishRaw(String payload, bool isGGA);
void publishHealth(String payload); // Thêm hàm gửi thông tin sức khỏe
bool isMqttConnected();             // Thêm hàm lấy trạng thái kết nối MQTT

#endif