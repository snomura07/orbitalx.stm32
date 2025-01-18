#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include <memory>
#include <Usart/usart.h>

class UsartInterface {
protected:
    std::weak_ptr<Usart> usartPtr;

public:
    UsartInterface();
    virtual ~UsartInterface();

    virtual void setUsart(std::shared_ptr<Usart> usart);

protected:
    void sendMessage(const char* msg);
    void sendInt(int16_t value);
    void sendLong(int32_t value);
    void sendFloat(float value);
    char receiveChar();
};

#endif
