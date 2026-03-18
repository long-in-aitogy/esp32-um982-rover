#include "NMEA_Parser.h"

double nmeaToDecimal(String nmeaPos, String dir) {
  if (nmeaPos.length() < 4) return 0.0;
  int dotIndex = nmeaPos.indexOf('.');
  if (dotIndex < 2) return 0.0; 
  int degrees = nmeaPos.substring(0, dotIndex - 2).toInt();
  double minutes = nmeaPos.substring(dotIndex - 2).toDouble();
  double decimal = degrees + (minutes / 60.0);
  if (dir == "S" || dir == "W") decimal = -decimal;
  return decimal;
}

String parseGGA_toJSON(gga_data_struct ggaData) {
  char jsonPayload[128];
  snprintf(jsonPayload, sizeof(jsonPayload), 
            "{\"lat\":%.7f,\"lon\":%.7f,\"rtk_status\":%s,\"satellites\":%s}", 
            ggaData.lat, ggaData.lon, ggaData.rtk_status.c_str(), ggaData.satellites.c_str());
            
  return String(jsonPayload);
}

boolean parseGGA_toStruct(String ggaMsg, gga_data_struct &ggaData) {
  int comma[15];
  int count = 0;
  for (int i = 0; i < ggaMsg.length(); i++) {
    if (ggaMsg[i] == ',') {
      comma[count++] = i;
      if (count >= 15) break;
    }
  }

  if (count >= 14) {
    String latStr = ggaMsg.substring(comma[1] + 1, comma[2]);
    String latDir = ggaMsg.substring(comma[2] + 1, comma[3]);
    String lonStr = ggaMsg.substring(comma[3] + 1, comma[4]);
    String lonDir = ggaMsg.substring(comma[4] + 1, comma[5]);
    String rtkStr = ggaMsg.substring(comma[5] + 1, comma[6]);
    String satStr = ggaMsg.substring(comma[6] + 1, comma[7]);

    if (latStr.length() > 0 && lonStr.length() > 0) {
      double latDD = nmeaToDecimal(latStr, latDir);
      double lonDD = nmeaToDecimal(lonStr, lonDir);
      
      ggaData.lat = latDD;
      ggaData.lon = lonDD;
      ggaData.rtk_status = rtkStr;
      ggaData.satellites = satStr;
               
      return true;
    }
  }
  return false;
}

String parseKSXT_toJSON(String ksxtMsg) {
  int comma[23];
  int count = 0;
  for (int i = 0; i < ksxtMsg.length(); i++) {
    if (ksxtMsg[i] == ',') {
      comma[count++] = i;
      if (count >= 23) break;
    }
  }

  if (count >= 22) {
    String heightStr = ksxtMsg.substring(comma[4] + 1, comma[5]);
    String headingStr = ksxtMsg.substring(comma[5] + 1, comma[6]);
    String pitchStr = ksxtMsg.substring(comma[6] + 1, comma[7]);
    String rollStr = ksxtMsg.substring(comma[7] + 1, comma[8]);
    String veloStr = ksxtMsg.substring(comma[8] + 1, comma[9]);
    char jsonPayload[192];
    snprintf(jsonPayload, sizeof(jsonPayload), 
             "{\"height_m\":%s,\"heading_deg\":%s,\"pitch_deg\":%s,\"roll_deg\":%s,\"velocity_kmh\":%s}", 
             heightStr.c_str(), headingStr.c_str(), pitchStr.c_str(), rollStr.c_str(), veloStr.c_str());
    return String(jsonPayload);
  }
  return ""; // Trả về rỗng nếu không parse được
}