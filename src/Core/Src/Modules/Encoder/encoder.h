#ifndef ENCODER_H
#define ENCODER_H
#include <UsartInterface/usart_interface.h>

class Encoder : public UsartInterface{
public:
    Encoder(ADC_HandleTypeDef &hadc2_);
    ~Encoder();
    void execAdc();
    void out();
private:
    void countUp();

private:
    ADC_HandleTypeDef *hadc2;
    uint32_t counter;
    uint16_t currVal;
    uint16_t preVal;

private:
    static constexpr uint16_t THRE_UP   = 3845;
    static constexpr uint16_t THRE_DOWN = 3835;
};

#endif
