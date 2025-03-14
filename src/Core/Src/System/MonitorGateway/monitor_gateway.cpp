#include "monitor_gateway.h"
#include <math.h>

MonitorGateway::MonitorGateway() {
    buffIndex = 0;
    memset(rxBuffer, 0, RX_BUFFER_SIZE);
    memset(txBuffer, 0, TX_BUFFER_SIZE);
}
MonitorGateway::~MonitorGateway(){}

bool MonitorGateway::receiveCheck() {
    if(!UtilInterface::isReceived()) return false;
    parseFromString();
    UtilInterface::startPolling();
    return true;
}

void MonitorGateway::parseFromString() {
    int size = UtilInterface::getRxBufferSize();
    UtilInterface::copyRxBuffer(rxBuffer, size);

    if (memcmp(rxBuffer, "[debug]@", 8) == 0) {
        sendMessage("get: [debug]@ \r\n");
    }
    else if (memcmp(rxBuffer, "[adc]@", 6) == 0) {
        sendMessage("get: [adc]@ \r\n");
    }
    else if (memcmp(rxBuffer, "[info]@", 7) == 0) {
        sendMessage("get: [info]@ \r\n");
    }
}

void MonitorGateway::addGraphData(char *label, float data) {
    int integerPart    = (int)data; // 整数部分
    int fractionalPart = (int)((fabs(data) - abs(integerPart)) * 1000); // 小数点以下3桁
    char tempBuffer[20];
    int written = sprintf(tempBuffer, "%s:%d.%03d,", label, integerPart, fractionalPart);

    if (written < 0 || buffIndex + written >= TX_BUFFER_SIZE) {
        return;
    }

    memcpy(&txBuffer[buffIndex], tempBuffer, written);
    buffIndex += written;
}

void MonitorGateway::sendGraphData() {
    sendMessage("[adc]@");
    sendMessage((char *)txBuffer);
    sendMessage("\r\n");

    memset(txBuffer, 0, TX_BUFFER_SIZE);
    buffIndex = 0;
}
