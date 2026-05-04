#include "util_interface.h"

UtilInterface::UtilInterface() {}

UtilInterface::~UtilInterface() {}

void UtilInterface::setUsartPtr(Usart *usart) {
    usartPtr = usart;
}

void UtilInterface::setParamPtr(Parameter *param) {
    paramPtr = param;
}

void UtilInterface::setLoggerPtr(Logger *logger) {
    loggerPtr = logger;
}

void UtilInterface::sendMessage(const char* msg) {
    usartPtr->sendString(msg);
}

void UtilInterface::sendInt(int16_t value) {
    usartPtr->sendInt16t(value);
}

void UtilInterface::sendLong(int32_t value) {
    usartPtr->sendInt32t(value);
}

void UtilInterface::sendFloat(float value) {
    usartPtr->sendFloat(value);
}

bool UtilInterface::isReceived() {
    return usartPtr->isReceived;
}

void UtilInterface::copyRxBuffer(uint8_t *dest, size_t size) {
    memcpy(dest, usartPtr->rxBuffer, size);
    usartPtr->clearBuff();
}

int UtilInterface::getRxBufferSize() {
    return usartPtr->rxIndex;
}

void UtilInterface::startPolling() {
    usartPtr->startPolling();
}

char UtilInterface::receiveChar() {
    char data = 0;
    data = usartPtr->receiveChar();
    return data;
}

char UtilInterface::receiveCharNonBlocking(){
    char data = 0;
    data = usartPtr->receiveCharNonBlocking();
    return data;
}

void UtilInterface::setLog1(int16_t val) {
    loggerPtr->setLog1(val);
}

void UtilInterface::setLog2(int16_t val) {
    loggerPtr->setLog2(val);
}

void UtilInterface::setLog3(int16_t val) {
    loggerPtr->setLog3(val);
}
