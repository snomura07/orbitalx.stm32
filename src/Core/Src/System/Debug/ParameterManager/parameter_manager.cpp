#include "parameter_manager.h"

namespace Debug {

ParameterManager::ParameterManager():
    rxIndex(0)
{}
ParameterManager::~ParameterManager(){}

bool ParameterManager::comCheck() {
    bool res = false;
    char received = receiveCharNonBlocking();
    if (received == '\0') return res;

    if (rxIndex < sizeof(rxBuffer) - 1) {
        rxBuffer[rxIndex++] = received;
    }

    if (received == '\n' || received == '\r') {
        rxBuffer[rxIndex] = '\0';

        if (strcmp(rxBuffer, "[debug]@") == 0) {
            sendMessage("[info]@デバッグモード有効");
        }

        rxIndex = 0;
        memset(rxBuffer, 0, sizeof(rxBuffer));
    }

}
};
