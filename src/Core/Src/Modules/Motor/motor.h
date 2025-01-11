#ifndef MOTOR_H
#define MOTOR_H
#include <UsartInterface/usart_interface.h>

class Motor : public UsartInterface{
public:
    Motor();
    ~Motor();
};

#endif
