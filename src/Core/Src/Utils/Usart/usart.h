#ifndef SRC_UTILS_USART_H_
#define SRC_UTILS_USART_H_

#include <main.h>
#include <stm32f3xx_hal.h>
#ifdef __cplusplus
    #include <cstring>
    #include <cstdio>
#endif

class Usart{
public:
    Usart(UART_HandleTypeDef &huart_);
    ~Usart();
    void sendString(const char *str);
    void sendInt16t(int16_t value);
    void sendUint16t(uint16_t value);
    void sendInt32t(int32_t value);
    void sendUint32t(uint32_t value);
    void sendFloat(float value, uint8_t precision);

private:
    UART_HandleTypeDef *huart;
};

#endif
