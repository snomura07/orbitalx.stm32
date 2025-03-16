#include "monitor_gateway.h"
#include <math.h>
#include <Custom/custom.h>

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

    if (memcmp(rxBuffer, "[debug]@", strlen("[debug]@")) == 0) {
        sendInfoData();
    }
    else if (memcmp(rxBuffer, "[adc]@", strlen("[adc]@")) == 0) {
        sendMessage("get: [adc]@ \r\n");
    }
    else if (memcmp(rxBuffer, "[info]@", strlen("[info]@")) == 0) {
        parseInfoData();
    }
}

void MonitorGateway::parseInfoData() {
    char* ptr = (char*)rxBuffer + 7;  // "[info]@" をスキップ
    char* lastParam = nullptr;

    while (*ptr) {
        char* comma = strchr(ptr, ',');  // カンマの検索
        if (comma) {
            *comma = '\0';          // カンマを '\0' に置換
            lastParam = comma + 1;
        }

        updateParam(ptr, (comma == nullptr));  //最後のパラメータのときだけtrueを渡す

        if (!comma) break;
        ptr = comma + 1;
    }
}

void MonitorGateway::updateParam(const char* keyValue, bool isLast) {
    char* separator = strchr(keyValue, ':');
    if (!separator) return;

    *separator = '\0';
    const char* key = keyValue;
    const char* value = separator + 1;

    float val = Custom::strToFloat(value);
    if(memcmp(key, "MACHINE_NAME", strlen("MACHINE_NAME")) == 0) {
        strncpy(paramPtr->machineName, value, sizeof(paramPtr->machineName) - 1);
        paramPtr->machineName[sizeof(paramPtr->machineName) - 1] = '\0';
    }
    else if(memcmp(key, "VERSION", strlen("VERSION")) == 0) {
        strncpy(paramPtr->version, value, sizeof(paramPtr->version) - 1);
        paramPtr->version[sizeof(paramPtr->version) - 1] = '\0';
    }
    else if(memcmp(key, "GAIN_VEL_KP", strlen("GAIN_VEL_KP")) == 0){
        paramPtr->pidGainVel.kP = val;
    }
    else if(memcmp(key, "GAIN_VEL_KI", strlen("GAIN_VEL_KI")) == 0){
        paramPtr->pidGainVel.kI = val;
    }
    else if(memcmp(key, "GAIN_VEL_KD", strlen("GAIN_VEL_KD")) == 0){
        paramPtr->pidGainVel.kD = val;
    }

    if (isLast) {
        paramPtr->writeAll();
        sendMessage("dataflash write complete!");
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

void MonitorGateway::sendInfoData() {
    sendMessage("[info]@");

    sendMessage("MACHINE_NAME:");
    sendMessage(paramPtr->machineName);
    sendMessage(",VERSION:");
    sendMessage(paramPtr->version);

    sendMessage(",GAIN_VEL_KP:");
    sendFloat(paramPtr->pidGainVel.kP);
    sendMessage(",GAIN_VEL_KI:");
    sendFloat(paramPtr->pidGainVel.kI);
    sendMessage(",GAIN_VEL_KD:");
    sendFloat(paramPtr->pidGainVel.kD);
    sendMessage("\r\n");
}
