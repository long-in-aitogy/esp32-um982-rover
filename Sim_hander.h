#ifndef SIM_HANDLER_H
#define SIM_HANDLER_H

#define TINY_GSM_MODEM_SIM7600
// Set serial for debug console
#define SerialMon Serial

// Set serial for AT commands
#define SerialAT Serial2

// See all AT commands
#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>

#endif