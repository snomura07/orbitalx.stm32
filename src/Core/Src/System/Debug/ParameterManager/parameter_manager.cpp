#include "parameter_manager.h"

namespace Debug {

ParameterManager::ParameterManager():
    rxIndex(0)
{}
ParameterManager::~ParameterManager(){}

bool ParameterManager::comCheck() {
    if(!UtilInterface::isReceived()) return false;

    int size = UtilInterface::getRxBufferSize();
    uint8_t buff[size];
    UtilInterface::copyRxBuffer(buff, size);

    if (memcmp(buff, "[debug]@", 8) == 0) {
        float gg = 0.001;
        sendMessage("[info]@");
        sendMessage("GAIN1:");
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN2:");
        gg = 1.0;
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN3:");
        gg = 13.0;
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN4:");
        gg = 0.987;
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN5:");
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN6:");
        sendFloat(gg);
        sendMessage(",");
        sendMessage("GAIN7:");
        sendFloat(gg);
        sendMessage("\r\n");

    }

    return true;
}
};
