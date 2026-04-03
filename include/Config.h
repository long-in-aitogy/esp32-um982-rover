#ifndef CONFIG_H
#define CONFIG_H

#define CONNECT_USING_WIFI false
#define TINY_GSM_MODEM_SIM7600

// ================= CẤU HÌNH PHẦN CỨNG =================
#define RX_GNSS 26 // Nối TXD (Hàng dưới) của UM980
#define TX_GNSS 27 // Nối RXD (Hàng dưới) của UM980
#define GNSS_BAUD 115200

// ================= CẤU HÌNH MẠNG & MQTT =================
#define WIFI_SSID "AITOGY"
#define WIFI_PASS "aitogy@aitogy"

#define MQTT_SERVER "aitogy.asia"
#define MQTT_PORT 1883
#define MQTT_USER "mqttUser"
#define MQTT_PASS "MqttPassword123$%^"

#define TOPIC_PUB_DATA_GGA "tdm2402/um980/data/gga"
#define TOPIC_PUB_DATA_KSXT "tdm2402/um980/data/ksxt"
#define TOPIC_SUB_CMD "tdm2402/um980/cmd"
#define TOPIC_PUB_RAW_GGA "tdm2402/um980/raw/gga"
#define TOPIC_PUB_RAW_KSXT "tdm2402/um980/raw/ksxt"
#define TOPIC_PUB_HEALTH "tdm2402/um980/health"

// ================= CẤU HÌNH NTRIP =================
// 1 = PUSH BASE, 2 = PULL NO NMEA, 3 = PULL WITH NMEA
#define NTRIP_MODE 3

#define NTRIP_CASTER_IP                                                        \
  "aitogy.com.vn" // THAY BẰNG IP HOẶC DOMAIN CASTER CỦA BẠN
#define NTRIP_CASTER_PORT 2101
#define NTRIP_MOUNTPOINT "/humga"
// Base64 của "trung:12345"
#define NTRIP_AUTH "dHJ1bmc6MTIzNDU="

#endif