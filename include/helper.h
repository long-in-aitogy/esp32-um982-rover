#ifndef HELPER_H
#define HELPER_H

#include "Top_Lvl_Config.h"
#include "Prog_Config.h"
#include <Arduino.h>
#include "functions/MQTT_Manager.h"
#include "functions/NTRIP_Handler_IP.h"
#include "functions/NMEA_Parser.h"
#include "DataStructs.h"

// ================= ĐỊNH NGHĨA CÁC HẰNG SỐ =================

// ================= ĐỊNH NGHĨA CÁC BIẾN TOÀN CỤC =================
inline String nmeaBuffer = "";
inline String latestGGA = "";

// ================= ĐỊNH NGHĨA CÁC ĐỐI TƯỢNG CẦN CHO KẾT NỐI =================
#if CONNECT_USING_WIFI
#include "hardware/Wifi_handler.h"
WiFiClient espClient;
WiFiClient ntripClient;
#endif
#if CONNECT_USING_4G
#include "hardware/Sim_handler.h"
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
inline TinyGsm        modem(debugger);
#else
inline TinyGsm        modem(Serial);
#endif
inline TinyGsmClient espClient(modem);
inline TinyGsmClient ntripClient(modem);
#endif

inline PubSubClient mqtt(espClient);

// ================= ĐỊNH NGHĨA CÁC HÀM =================
void sendDeviceHealth();

#endif