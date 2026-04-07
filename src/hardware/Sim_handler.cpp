#include "hardware/Sim_handler.h"

void setupGSM(TinyGsm &modem) {
    int retrys = 1;
    SerialMon.println("Initializing modem... Attempt: " + String(retrys));
    modem.restart();
    String modemInfo = modem.getModemInfo();
    while (modemInfo.length() == 0) {
        if (retrys > 5) {
            SerialMon.println("Failed to initialize modem after multiple attempts");
            return;
        }
        SerialMon.println("Failed to get modem info, retrying... Attempt: " 
            + String(retrys));
        delay(1000);
        modem.restart();
        modemInfo = modem.getModemInfo();
        retrys++;
    }
    SerialMon.print("Modem Info: ");
    SerialMon.println(modemInfo);

    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    delay(3000);
    
    SerialMon.println("Connecting to GSM network...");
    if (!modem.waitForNetwork()) {
        SerialMon.println("Failed to connect to GSM network");
        return;
    }
    
    if (modem.isNetworkConnected()) {
        SerialMon.println("GSM network connected");
    } else {
        SerialMon.println("GSM network connection failed");
        return;
    }

    int csq = modem.getSignalQuality();
    SerialMon.print("Signal quality: " + String(csq));

    SerialMon.print("Connecting to APN: ");
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
            SerialMon.println(" - Fail !");
            delay(10000);
            return;
    }
    SerialMon.println(" - Success !");
    if (modem.isGprsConnected()) {
        SerialMon.println("GPRS connected");
    }
    IPAddress local = modem.localIP();
    SerialMon.println("Local IP: " + local.toString());
}