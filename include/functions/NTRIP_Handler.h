#ifndef NTRIP_HANDLER_H
#define NTRIP_HANDLER_H

// ============ GẮN CÁC THƯ VIỆN CẦN THIẾT ==============

#include <Arduino.h>

#if CONNECT_USING_WIFI
#include <WiFiClient.h>
#include "wifi_handler.h"
typedef WiFiClient ClientType;
#else
#include "../hardware/Sim_handler.h"
#include <TinyGsmClient.h>
typedef TinyGsmClient ClientType;
#endif

// =============== KHAI BÁO HÀM =================

void setupNTRIP();
void loopNTRIP(ClientType &ntripClient, String currentGGA);
bool isNtripConnected(); // Thêm hàm lấy trạng thái NTRIP

#endif