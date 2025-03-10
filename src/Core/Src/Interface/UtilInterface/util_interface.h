#ifndef util_interface_H_
#define util_interface_H_

#include <memory>
#include <Usart/usart.h>
#include <Parameter/parameter.h>

class UtilInterface {
protected:
    Usart *usartPtr;
    Parameter *paramPtr;

public:
    UtilInterface();
    virtual ~UtilInterface();

    virtual void setUsartPtr(Usart *usart);
    virtual void setParamPtr(Parameter *param);

protected:
    void sendMessage(const char* msg);
    void sendInt(int16_t value);
    void sendLong(int32_t value);
    void sendFloat(float value);
    char receiveChar();
    char receiveCharNonBlocking();
};

#endif
