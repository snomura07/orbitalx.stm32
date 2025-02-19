#ifndef ADC_H
#define ADC_H
#include <stm32g4xx_hal.h>
#include <Iled/i_led.h>

class Adc {
public:
    static Adc* instance;
public:
    Adc(ADC_HandleTypeDef &hadc_, Iled *iled_);
    ~Adc();
    void startDMA();
    void handleDMAComplete();
    uint16_t adcValues[7];

private:
    ADC_HandleTypeDef *hadc;
    Iled *iled;
};

#endif
