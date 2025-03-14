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
    sprintf(buffer, "%d", value);
    sendString(buffer);
}
void Usart::sendUint16t(uint16_t value){
    char buffer[10];
    sprintf(buffer, "%u", value);
    sendString(buffer);
}

void Usart::sendInt32t(int32_t value){
    char buffer[11];
    sprintf(buffer, "%ld", value);
    sendString(buffer);
}
void Usart::sendUint32t(uint32_t value){
    char buffer[11];
    sprintf(buffer, "%lu", value);
    sendString(buffer);
}
void Usart::sendFloat(float value){
    int integerPart    = (int)value; // 整数部分
    int fractionalPart = (int)((fabs(value) - abs(integerPart)) * 1000); // 小数点以下3桁

    char buffer[20];
    if (value < 0) {
        sprintf(buffer, "-%d.%03d", abs(integerPart), fractionalPart);
    } else {
        sprintf(buffer, "%d.%03d", integerPart, fractionalPart);
    }
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
