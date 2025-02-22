#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H
#include <UsartInterface/usart_interface.h>
#include <Iled/i_led.h>
#include <Adc/adc.h>

class WallSensor : public UsartInterface{
public:
    WallSensor(Adc *adc_, Iled *ied_);
    ~WallSensor();
    void update();
    void dump();

private:
    Adc *adc;
    Iled *iled;
    uint16_t rFront;
    uint16_t rSide;
    uint16_t lFront;
    uint16_t lSide;
    bool isIledOn;
};

#endif
