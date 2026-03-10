# ESP32 GNSS Gateway (UM980 / UM982)

Firmware dành cho vi điều khiển ESP32 (ví dụ board TDM2402) đóng vai trò làm Gateway kết nối với module GNSS định vị động học thời gian thực (RTK) như Unicore UM980 hoặc UM982. 

## Tính năng chính
- **Giao tiếp GNSS**: Đọc dữ liệu NMEA (như `$GNGGA`, `$GPGGA`) từ module UM980/UM982 qua Serial.
- **Phân tích dữ liệu**: Trích xuất các thông số tọa độ (Latitude, Longitude), số lượng vệ tinh, trạng thái RTK từ chuỗi NMEA và đóng gói thành định dạng JSON.
- **MQTT Publisher**: Gửi dữ liệu vị trí JSON lên MQTT Broker để giám sát tọa độ theo thời gian thực.
- **NTRIP Client**: Kết nối đến NTRIP Caster, nhận dữ liệu cải chính định vị (RTCM) và đẩy ngược lại cho module GNSS để đạt được độ chính xác RTK (mức cm). Hỗ trợ truyền lại chuỗi GGA cho Caster để xác thực.
- **Giám sát trạng thái (Health Check)**: Định kỳ báo cáo các thông số như RAM trống, Uptime, cường độ tín hiệu WiFi, trạng thái MQTT/NTRIP và chất lượng dữ liệu GNSS.

## Yêu cầu môi trường (Arduino IDE / CLI)
- ESP32 Core: `esp32:esp32`
- Thư viện yêu cầu: `PubSubClient` (Bởi Nick O'Leary)

## Cấu hình hệ thống
Mọi thông số kết nối được đặt trong file `Config.h`:
- Thiết lập chân UART kết nối với module GNSS (`RX_GNSS`, `TX_GNSS`)
- Thông tin mạng WiFi (`SSID`, `Password`)
- Cấu hình kết nối MQTT (`Server`, `Port`, `User`, `Pass`, `Topics`)
- Cấu hình tài khoản NTRIP (`Caster IP`, `Port`, `Mountpoint`, `Base64 Auth`)
