#ifndef SRC_UTILS_USART_H_
#define SRC_UTILS_USART_H_

#include <main.h>
#include <MasterDefine.h>
#ifdef __cplusplus
    #include <cstring>
    #include <cstdio>
#endif

class Usart{
public:
    static Usart* instance;
    uint8_t rxBuffer[RX_BUFFER_SIZE];
    bool isReceived;
    uint8_t rxIndex;
    uint8_t receivedChar;

public:
    Usart(UART_HandleTypeDef &huart_);
    ~Usart();
    void sendString(const char *str);
    void sendInt16t(int16_t value);
    void sendUint16t(uint16_t value);
    void sendInt32t(int32_t value);
    void sendUint32t(uint32_t value);
    void sendFloat(float value);

    void startPolling();
    void clearBuff();
    void buffCheck();

    char receiveChar();
    char receiveCharNonBlocking();

private:
    UART_HandleTypeDef *huart;
};

#endif
