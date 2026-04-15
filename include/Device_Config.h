/*
    Cấu hình cho thiết bị ĐỂ SỬ DỤNG TẠI MAIN.CPP
*/
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#define WIFI_LORA_32_V4
#define LORAWAN_DEBUG_LEVEL 0
#define CONNECT_USING_WIFI 1
#define CONNECT_USING_LORA 0
#define CONNECT_USING_4G 0

#if (!CONNECT_USING_WIFI && !CONNECT_USING_4G && !CONNECT_USING_LORA)
    #warning "Không chọn phương thức kết nối nào! Sẽ sử dụng WiFi."
    #undef CONNECT_USING_WIFI
    #define CONNECT_USING_WIFI 1
#endif

#if ((CONNECT_USING_WIFI + CONNECT_USING_4G + CONNECT_USING_LORA) > 1)
    #error "Chỉ được chọn một phương thức kết nối! Vui lòng chỉnh sửa DEVICE_CONFIG.h"
#endif

// ================= CẤU HÌNH PHẦN CỨNG =================
const int RX_GNSS = 26; // Nối TXD (Hàng dưới) của UM980
const int TX_GNSS = 27; // Nối RXD (Hàng dưới) của UM980
const int GNSS_BAUD = 115200;

#endif