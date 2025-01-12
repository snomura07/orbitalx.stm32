#include "usart.h"

Usart::Usart(UART_HandleTypeDef &huart_){
    this->huart = &huart_;
}
Usart::~Usart(){}

void Usart::sendString(const char *str){
    HAL_UART_Transmit(this->huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void Usart::sendInt16t(int16_t value){
    char buffer[10];
    sprintf(buffer, "%d", value);
    this->sendString(buffer);
}
void Usart::sendUint16t(uint16_t value){
    char buffer[10];
    sprintf(buffer, "%u", value);
    this->sendString(buffer);
}

void Usart::sendInt32t(int32_t value){
    char buffer[11];
    sprintf(buffer, "%ld", value);
    this->sendString(buffer);
}
void Usart::sendUint32t(uint32_t value){
    char buffer[11];
    sprintf(buffer, "%lu", value);
    this->sendString(buffer);
}
