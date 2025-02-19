#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H
#include <UsartInterface/usart_interface.h>
#include <Iled/i_led.h>
#include <Adc/adc.h>

class WallSensor : public UsartInterface{
public:
    struct WallSensInfo
    {
        uint16_t on;
        uint16_t off;
        uint16_t filtered;
    };


public:
    WallSensor(Adc *adc_, Iled *ied_);
    ~WallSensor();
    void update();
    void dump();

private:
    Adc *adc;
    Iled *iled;
    WallSensInfo rFront;
    WallSensInfo rSide;
    WallSensInfo lFront;
    WallSensInfo lSide;
    bool isIledOn;
};

#endif
