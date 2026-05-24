#include "usart.h"
#include <math.h>

Usart* Usart::instance = nullptr;

Usart::Usart(UART_HandleTypeDef &huart_){
    huart        = &huart_;
    instance     = this;
    isReceived   = false;
    rxIndex      = 0;
    receivedChar = 0;
    clearBuff();
}
Usart::~Usart(){}

void Usart::sendString(const char *str){
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void Usart::sendInt16t(int16_t value){
    char buffer[10];
    int32ToString(static_cast<int32_t>(value), buffer);
    sendString(buffer);
}
void Usart::sendUint16t(uint16_t value){
    char buffer[10];
    uint32ToString(static_cast<uint32_t>(value), buffer);
    sendString(buffer);
}

void Usart::sendInt32t(int32_t value){
    char buffer[12];
    int32ToString(value, buffer);
    sendString(buffer);
}
void Usart::sendUint32t(uint32_t value){
    char buffer[11];
    uint32ToString(value, buffer);
    sendString(buffer);
}
void Usart::sendFloat(float value){
    char buffer[20];
    uint32_t index = 0;

    if (value < 0.0f) {
        buffer[index++] = '-';
    }

    float absValue = fabsf(value);
    uint32_t integerPart = static_cast<uint32_t>(absValue);
    float fractional = (absValue - static_cast<float>(integerPart)) * 1000.0f;
    uint32_t fractionalPart = static_cast<uint32_t>(fractional + 0.5f);

    if (fractionalPart >= 1000U) {
        integerPart++;
        fractionalPart = 0U;
    }

    index += uint32ToString(integerPart, buffer + index);
    buffer[index++] = '.';
    appendFixed3Digits(fractionalPart, buffer + index);

    sendString(buffer);
}

void Usart::startPolling() {
    HAL_UART_Receive_IT(huart, &receivedChar, 1);
}

/*******************************/
/*                             */
/*                             */
/* HAL callback function       */
/*                             */
/*                             */
/*******************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  {
    if (huart->Instance == USART1) {
        // 受信データを格納
        uint8_t receivedChar = Usart::instance->receivedChar;
        Usart::instance->rxBuffer[Usart::instance->rxIndex] = receivedChar;

        if (receivedChar == '\n') {
            Usart::instance->rxBuffer[Usart::instance->rxIndex] = '\0'; // \n を \0 に置換
            Usart::instance->isReceived = true;
        }
        else {
            // 次の受信を開始
            Usart::instance->rxIndex++;
            Usart::instance->startPolling();
        }
    }
}

void Usart::clearBuff(){
    rxIndex    = 0;
    isReceived = false;
    memset(rxBuffer, 0, RX_BUFFER_SIZE);
}

void Usart::buffCheck() {
    sendString("check: ");
    sendInt16t(isReceived);
    sendString(" recv: ");
    sendString((char *)rxBuffer);
    sendString("\r\n");
}

char Usart::receiveChar(){
    uint8_t received;
    HAL_UART_Receive(huart, &received, 1, 1000);
    return (char)received;
}

char Usart::receiveCharNonBlocking(){
    uint8_t received;
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE)) {
        if (HAL_UART_Receive(huart, &received, 1, 0) == HAL_OK) {
            return (char)received;
        }
    }
    return '\0';
}


uint16_t Usart::uint32ToString(uint32_t value, char *buffer) {
    char temp[10];
    uint16_t digits = 0;

    do {
        temp[digits++] = static_cast<char>('0' + (value % 10U));
        value /= 10U;
    } while (value > 0U);

    for (uint16_t i = 0; i < digits; i++) {
        buffer[i] = temp[digits - 1U - i];
    }
    buffer[digits] = '\0';
    return digits;
}

void Usart::int32ToString(int32_t value, char *buffer) {
    if (value < 0) {
        buffer[0] = '-';
        uint32_t magnitude = static_cast<uint32_t>(-(value + 1)) + 1U;
        uint32ToString(magnitude, buffer + 1);
        return;
    }

    uint32ToString(static_cast<uint32_t>(value), buffer);
}

void Usart::appendFixed3Digits(uint32_t value, char *buffer) {
    buffer[0] = static_cast<char>('0' + ((value / 100U) % 10U));
    buffer[1] = static_cast<char>('0' + ((value / 10U) % 10U));
    buffer[2] = static_cast<char>('0' + (value % 10U));
    buffer[3] = '\0';
}
