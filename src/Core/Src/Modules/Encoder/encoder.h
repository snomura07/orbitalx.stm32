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
    static constexpr uint8_t WINDOW_SIZE = 10;
    uint16_t encWindow[WINDOW_SIZE];
    uint32_t ave;
    uint32_t counter;
    bool inMotion;
};

#endif
