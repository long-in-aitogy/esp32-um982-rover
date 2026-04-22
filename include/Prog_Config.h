#ifndef PROG_CONFIG_H
#define PROG_CONFIG_H

#include "Top_Lvl_Config.h"

// ================= CẤU HÌNH CHÂN CẮM VÀ TỐC ĐỘ SERIAL =================
#define RX_GNSS 26 // Nối TXD (Hàng dưới) của UM980
#define TX_GNSS 27 // Nối RXD (Hàng dưới) của UM980
#define GNSS_BAUD 115200

// ================= CẤU HÌNH KẾT NỐI =================
#if CONNECT_USING_WIFI
#define WIFI_SSID "AITOGY"
#define WIFI_PASS "aitogy@aitogy"
#endif

#if CONNECT_USING_4G
#define TX_TO_MODEM_RX 16 // uint8_t
#define RX_TO_MODEM_TX 17 // uint8_t
#define MODEM_DC_PIN 15 // uint8_t
#define MODEM_DTR_PIN 4 // uint8_t

#define APN "v-internet" // Thay bằng APN của nhà mạng bạn
#define GPRS_USER ""     // Thường để trống
#define GPRS_PASS ""
#endif

// ================= CẤU HÌNH NTRIP =================
#define NTRIP_MODE 3 // 1: Chỉ gửi GGA khi có yêu cầu; 2: Gửi GGA mỗi khi có thay đổi; 3: Gửi GGA đều đặn mỗi 10s

#if NTRIP_COMMUNICATION_PROTOCOL == TCP_IP
#define NTRIP_CASTER_IP "aitogy.com.vn"
#define NTRIP_CASTER_PORT 2101  // uint16_t
#elif NTRIP_COMMUNICATION_PROTOCOL == LORA_SERIAL
#define NTRIP_LORA_SERIAL_CONFIG
#endif

#define NTRIP_MOUNTPOINT "/humga"
// Base64 của "trung:12345"
#define NTRIP_AUTH "dHJ1bmc6MTIzNDU="

// ================ CẤU HÌNH MQTT =================

#define MQTT_SERVER "aitogy.asia"
#define MQTT_PORT 1883   // uint16_t
#define MQTT_USER "mqttUser"
#define MQTT_PASS "MqttPassword123$%^"

#define TOPIC_PUB_DATA_GGA "tdm2402/um980/data/gga"
#define TOPIC_PUB_DATA_KSXT "tdm2402/um980/data/ksxt"
#define TOPIC_SUB_CMD "tdm2402/um980/cmd"
#define TOPIC_PUB_RAW_GGA "tdm2402/um980/raw/gga"
#define TOPIC_PUB_RAW_KSXT "tdm2402/um980/raw/ksxt"
#define TOPIC_PUB_HEALTH "tdm2402/um980/health"

#endif // PROG_CONFIG_H