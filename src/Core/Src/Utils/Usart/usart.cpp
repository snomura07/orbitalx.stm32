#include "usart.h"
#include <math.h>

Usart* Usart::instance = nullptr;

Usart::Usart(UART_HandleTypeDef &huart_){
    huart        = &huart_;
    instance     = this;
    receivedChar = 0;
    clearBuff();
    startSequentialReceive();
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

void Usart::startSequentialReceive() {
    // HAL_UART_Receive_IT(huart, &receivedChar, 1);
}


/*******************************/
/*                             */
/*                             */
/* HAL callback function       */
/*                             */
/*                             */
/*******************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  {
    // Usart::instance->sendString("ok \r\n");

    // if (huart->Instance == USART1) {

    //     // 1 バイト受信したら発火
    //     Usart::instance->received();
    // }
}

void Usart::received() {
    if (receivedChar == '\n') {     // 改行を受信したらメッセージの終端と判断
        rxBuffer[rxIndex] = '\0';   // 文字列の終端を追加
    } 
    else {
        if (rxIndex < RX_BUFFER_SIZE - 1) {
            rxBuffer[rxIndex++] = receivedChar;
        }
    }

    // 次の 1 バイトを受信開始
    HAL_UART_Receive_IT(huart, &receivedChar, 1);

}

void Usart::clearBuff(){
    rxIndex = 0;
    memset(rxBuffer, 0, RX_BUFFER_SIZE);
}

void Usart::buffCheck(){
    sendString("index: ");
    sendInt16t(rxIndex);
    sendString(" received: ");
    sendString((char*)rxBuffer);
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
