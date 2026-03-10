#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include <Arduino.h>

// Hàm chuyển đổi DDMM.MMMM sang Decimal
double nmeaToDecimal(String nmeaPos, String dir);

// Hàm nhận chuỗi GGA gốc và trả về chuỗi JSON
String parseGGA_toJSON(String ggaMsg);

#endif