#ifndef ADC_H
#define ADC_H
#include <stm32g4xx_hal.h>
#include <Iled/i_led.h>

class Adc {
public:
    static Adc* instance;
    static constexpr uint8_t BUFF_SIZE    = 200;
    uint16_t adcBuff[7];
    uint16_t rightEncBuff[BUFF_SIZE];
    uint16_t leftEncBuff[BUFF_SIZE];
    int rightEncWriteIndex;
    int rightEncDataCount;
    int leftEncWriteIndex;
    int leftEncDataCount;
public:
    Adc(ADC_HandleTypeDef &hadc_, Iled *iled_);
    ~Adc();
    void startDMA();
    void handleDMAComplete();
    uint16_t getLatestValue(int channel);
    void resetEncDataCount();

private:
    ADC_HandleTypeDef *hadc;
    Iled *iled;
};

#endif
