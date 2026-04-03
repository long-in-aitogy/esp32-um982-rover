#ifndef SIM_HANDLER_H
#define SIM_HANDLER_H

#define TINY_GSM_MODEM_SIM7600
// Set serial for debug console
#define SerialMon Serial

// Set serial for AT commands
#define SerialAT Serial2

// See all AT commands
// #define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon

// pins
#define MODEM_RX 17
#define MODEM_TX 16
// #define MODEM_RESET_PIN 4

#include <TinyGsmClient.h>

const char apn[]      = "v-internet";  // Thay bằng APN của nhà mạng bạn
const char gprsUser[] = "";
const char gprsPass[] = "";

void setupGSM(TinyGsm &modem);

#endif