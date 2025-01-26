#ifndef BATTERY_H
#define BATTERY_H
#include <UsartInterface/usart_interface.h>

class Battery : public UsartInterface{
public:
    Battery(ADC_HandleTypeDef &hadc2_);
    ~Battery();
    void update();
    void dump();

private:
    void execAdc();

public:
    float volt;
    uint16_t mVolt;

private:
    ADC_HandleTypeDef *hadc2;
    uint16_t raw;

    static constexpr uint8_t BUFF_SIZE = 16;
    uint16_t mVoltBuff[BUFF_SIZE];
};

#endif
