#ifndef ENCODER_H
#define ENCODER_H
#include <UsartInterface/usart_interface.h>

class Encoder : public UsartInterface{
public:
    Encoder(ADC_HandleTypeDef &hadc2_);
    ~Encoder();
    void update();
    void dump();
private:
    void execAdc();
    void countUp();

private:
    ADC_HandleTypeDef *hadc2;
    uint32_t counter;
    uint16_t currRaw;
    uint16_t preRaw;

    uint16_t uCnt;
    uint16_t max;
    uint16_t min;
    uint16_t currThreUP;
    uint16_t currThreDown;

private:
    // static constexpr uint16_t THRE_UP   = 3845;
    // static constexpr uint16_t THRE_DOWN = 3835;
    uint16_t THRE_UP;
    uint16_t THRE_DOWN;
};

#endif
