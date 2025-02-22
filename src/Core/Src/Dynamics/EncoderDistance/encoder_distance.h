#ifndef ENCODER_DISTANCE_H
#define ENCODER_DISTANCE_H

#include <MasterDefine.h>
#include <UsartInterface/usart_interface.h>
#include <Encoder/encoder.h>

class EncoderDistance : public UsartInterface{
public:
    float mm;

public:
    EncoderDistance(Encoder *rightEncoder_, Encoder *leftEncoder_);
    ~EncoderDistance();
    void init();
    void update();
    void reset();
    void dump();

private:
    Encoder *rightEncoder;
    Encoder *leftEncoder;
    float rightCount2Dis;
    float leftCount2Dis;
};

#endif
