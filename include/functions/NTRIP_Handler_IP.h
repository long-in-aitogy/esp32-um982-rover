#ifndef NTRIP_HANDLER_IP_H
#define NTRIP_HANDLER_IP_H

// ============ GẮN CÁC THƯ VIỆN CẦN THIẾT ==============

#include <Arduino.h>
#include "Top_Lvl_Config.h"

// =============== KHAI BÁO HÀM =================

void setupNTRIP();
void loopNTRIP(String currentGGA);
bool isNtripConnected(); // Thêm hàm lấy trạng thái NTRIP

#endif