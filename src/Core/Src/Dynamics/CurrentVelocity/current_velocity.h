#ifndef DYNAMICS_CURRENT_VELOCITY_H
#define DYNAMICS_CURRENT_VELOCITY_H

#include <Encoder/encoder.h>
#include <dynamics_define.h>
#include <UsartInterface/usart_interface.h>

class CurrentVelocity : public UsartInterface{
public:
    CurrentVelocity();
    ~CurrentVelocity();
    void setEncoder(Encoder *right_encoder_, Encoder *left_encoder_);

private:
    Encoder *right_encoder;
    Encoder *left_encoder;
};

#endif
