#ifndef BATTERY_H
#define BATTERY_H
#include <UtilInterface/util_interface.h>
#include <Adc/adc.h>

class Battery : public UtilInterface{
public:
    Battery(Adc *adc_);
    ~Battery();
    void update();
    void dump();

private:
    void execAdc();

public:
    float volt;
    uint16_t mVolt;

private:
    Adc *adc;
    uint16_t raw;

    static constexpr uint8_t BUFF_SIZE = 16;
    uint16_t mVoltBuff[BUFF_SIZE];
};

#endif
