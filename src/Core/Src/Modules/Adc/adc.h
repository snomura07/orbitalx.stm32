#ifndef ADC_H
#define ADC_H
#include <UsartInterface/usart_interface.h>

class Adc : public UsartInterface{
public:
    Adc(ADC_HandleTypeDef &hadc_);
    ~Adc();
    void update();
    void dump();

private:
    void execAdc();

private:
    ADC_HandleTypeDef *hadc;
};

#endif
