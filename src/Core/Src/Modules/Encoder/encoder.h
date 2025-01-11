#ifndef ENCODER_H
#define ENCODER_H
#include <UsartInterface/usart_interface.h>

class Encoder : public UsartInterface{
public:
    Encoder();
    ~Encoder();
    void execAdc();
};

#endif
