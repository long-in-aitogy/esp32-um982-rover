#ifndef NTRIP_HANDLER_H
#define NTRIP_HANDLER_H

// ============ GẮN CÁC THƯ VIỆN CẦN THIẾT ==============

#include <Arduino.h>
#include "../Prog_Config.h"
#include "../Device_Config.h"

#if CONNECT_USING_WIFI
#include <WiFiClient.h>
typedef WiFiClient ClientType;
#endif
#if CONNECT_USING_4G
#include "../hardware/Sim_handler.h"
#include <TinyGsmClient.h>
typedef TinyGsmClient ClientType;
#endif

// =============== KHAI BÁO HÀM =================

void setupNTRIP();
void loopNTRIP(ClientType &ntripClient, String currentGGA);
bool isNtripConnected(); // Thêm hàm lấy trạng thái NTRIP

#endif