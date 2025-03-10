#include "util_interface.h"

UtilInterface::UtilInterface() {}

UtilInterface::~UtilInterface() {}

void UtilInterface::setUsartPtr(Usart *usart) {
    usartPtr = usart;
}

void UtilInterface::setParamPtr(Parameter *param) {
    paramPtr = param;
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
