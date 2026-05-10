#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H
#include <UtilInterface/util_interface.h>
#include <Iled/i_led.h>
#include <Adc/adc.h>

class WallSensor : public UtilInterface{
public:
    uint16_t rFront;
    uint16_t rSide;
    uint16_t lFront;
    uint16_t lSide;

public:
    WallSensor(Adc *adc_, Iled *ied_);
    ~WallSensor();
    void update();
    uint16_t rFrontDetected();
    void dump();

private:
    enum class SamplePhase : uint8_t {
        SET_OFF = 0,
        SAMPLE_OFF_SET_ON,
        SAMPLE_ON_COMPUTE
    };

    uint16_t rFrontOff;
    uint16_t rSideOff;
    uint16_t lFrontOff;
    uint16_t lSideOff;
    SamplePhase phase;

    Adc *adc;
    Iled *iled;
};

#endif
