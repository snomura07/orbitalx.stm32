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

private:
    ADC_HandleTypeDef *hadc2;
    uint16_t raw;
};

#endif
