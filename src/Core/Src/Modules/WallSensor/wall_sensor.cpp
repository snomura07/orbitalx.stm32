#include "wall_sensor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

WallSensor:: WallSensor(Adc *adc_, Iled *iled_):
    adc(adc_),
    iled(iled_),
    rFront(0),
    rSide(0),
    lFront(0),
    lSide(0),
    rFrontOff(0),
    rSideOff(0),
    lFrontOff(0),
    lSideOff(0),
    phase(SamplePhase::SET_OFF)
{}
WallSensor::~WallSensor(){}

void WallSensor::update(){
    switch (phase) {
        case SamplePhase::SET_OFF:
            iled->off();
            phase = SamplePhase::SAMPLE_OFF_SET_ON;
            break;

        case SamplePhase::SAMPLE_OFF_SET_ON:
            rFrontOff = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
            rSideOff  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
            lFrontOff = adc->adcBuff[LEFT_FRONT_WSENS_CH];
            lSideOff  = adc->adcBuff[LEFT_SIDE_WSENS_CH];
            iled->on();
            phase = SamplePhase::SAMPLE_ON_COMPUTE;
            break;

        case SamplePhase::SAMPLE_ON_COMPUTE: {
            const int rFrontOn = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
            const int rSideOn  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
            const int lFrontOn = adc->adcBuff[LEFT_FRONT_WSENS_CH];
            const int lSideOn  = adc->adcBuff[LEFT_SIDE_WSENS_CH];

            rFront = static_cast<uint16_t>(rFrontOn - rFrontOff);
            rSide  = static_cast<uint16_t>(rSideOn  - rSideOff);
            lFront = static_cast<uint16_t>(lFrontOn - lFrontOff);
            lSide  = static_cast<uint16_t>(lSideOn  - lSideOff);

            iled->off();
            phase = SamplePhase::SAMPLE_OFF_SET_ON;
            break;
        }
    }
}

uint16_t WallSensor::rFrontDetected() {
    return rFront>1200 ? 1 : 0;
}

void WallSensor::dump(){
    sendMessage("rFront:");
    sendInt(rFront);
    sendMessage(", ");
    sendMessage("rSide:");
    sendInt(rSide);
    sendMessage(", ");
    sendMessage("lFront:");
    sendInt(lFront);
    sendMessage(", ");
    sendMessage("lSide:");
    sendInt(lSide);
    sendMessage("\r\n");
}
