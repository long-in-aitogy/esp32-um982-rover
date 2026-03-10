#ifndef NTRIP_HANDLER_H
#define NTRIP_HANDLER_H

#include <Arduino.h>
#include <WiFiClient.h>

void setupNTRIP();
void loopNTRIP(String currentGGA);
bool isNtripConnected(); // Thêm hàm lấy trạng thái NTRIP

#endif