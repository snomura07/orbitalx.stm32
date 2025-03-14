#ifndef SYSTEM_MONITOR_GATEWAY_H_
#define SYSTEM_MONITOR_GATEWAY_H_
#include <main.h>
#include <MasterDefine.h>
#include "UtilInterface/util_interface.h"

class MonitorGateway : public UtilInterface {
public:
    MonitorGateway();
    ~MonitorGateway();
    bool receiveCheck();
    void addGraphData(char *label, float data);
    void sendGraphData();

private:
    void parseFromString();
    void serializeToString();

private:
    uint8_t rxBuffer[RX_BUFFER_SIZE];
    uint8_t txBuffer[TX_BUFFER_SIZE];
    uint8_t buffIndex;
};

#endif
