#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

// ============= GẮN THƯ VIỆN CẦN THIẾT =============
#include <WiFi.h>
#include "../Prog_Config.h"

// ================= CẤU HÌNH WI-FI =================
const char* WIFI_SSID = "AITOGY";
const char* WIFI_PASS = "aitogy@aitogy";

void setupWiFi();

#endif