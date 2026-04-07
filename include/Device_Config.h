/*
    Cấu hình cho thiết bị ĐỂ SỬ DỤNG TẠI MAIN.CPP
*/
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#define CONNECT_USING_WIFI false


// ================= CẤU HÌNH PHẦN CỨNG =================
const int RX_GNSS = 26; // Nối TXD (Hàng dưới) của UM980
const int TX_GNSS = 27; // Nối RXD (Hàng dưới) của UM980
const int GNSS_BAUD = 115200;

#endif