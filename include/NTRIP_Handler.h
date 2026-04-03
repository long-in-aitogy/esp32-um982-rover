#ifndef NTRIP_HANDLER_H
#define NTRIP_HANDLER_H

#include <Arduino.h>
#include "Config.h"

#if CONNECT_USING_WIFI
#include <WiFiClient.h>
typedef WiFiClient ClientType;
#else
#include <TinyGsmClient.h>
typedef TinyGsmClient ClientType;
#endif

void setupNTRIP();
void loopNTRIP(ClientType &ntripClient, String currentGGA);
bool isNtripConnected(); // Thêm hàm lấy trạng thái NTRIP

#endif