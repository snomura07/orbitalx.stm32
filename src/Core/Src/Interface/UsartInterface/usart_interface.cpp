#include "usart_interface.h"

UsartInterface::UsartInterface() {}

UsartInterface::~UsartInterface() {}

void UsartInterface::setUsart(std::shared_ptr<Usart> usart) {
    usartPtr = usart;
}

void UsartInterface::sendMessage(const char* msg) {
    if (auto usart = usartPtr.lock()) {
        usart->sendString(msg);
    }
}

void UsartInterface::sendInt(int16_t value) {
    if (auto usart = usartPtr.lock()) {
        usart->sendInt16t(value);
    }
}

void UsartInterface::sendLong(int32_t value) {
    if (auto usart = usartPtr.lock()) {
        usart->sendInt32t(value);
    }
}

void UsartInterface::sendFloat(float value) {
    if (auto usart = usartPtr.lock()) {
        usart->sendFloat(value);
    }
}

char UsartInterface::receiveChar() {
    char data = 0;
    if (auto usart = usartPtr.lock()) {
        data = usart->receiveChar();
    }
    return data;
}
