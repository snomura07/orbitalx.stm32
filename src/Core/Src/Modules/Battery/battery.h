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

private:
    ADC_HandleTypeDef *hadc2;
    uint16_t raw;
    float volt;
};

#endif
