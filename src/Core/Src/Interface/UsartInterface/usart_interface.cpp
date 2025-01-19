#include "usart_interface.h"

UsartInterface::UsartInterface() {}

UsartInterface::~UsartInterface() {}

void UsartInterface::setUsart(Usart *usart) {
    usartPtr = usart;
}

void UsartInterface::sendMessage(const char* msg) {
    usartPtr->sendString(msg);
}

void UsartInterface::sendInt(int16_t value) {
    usartPtr->sendInt16t(value);
}

void UsartInterface::sendLong(int32_t value) {
    usartPtr->sendInt32t(value);
}

void UsartInterface::sendFloat(float value) {
    usartPtr->sendFloat(value);
}

char UsartInterface::receiveChar() {
    char data = 0;
    data = usartPtr->receiveChar();
    return data;
}

char UsartInterface::receiveCharNonBlocking(){
    char data = 0;
    data = usartPtr->receiveCharNonBlocking();
    return data;
}
