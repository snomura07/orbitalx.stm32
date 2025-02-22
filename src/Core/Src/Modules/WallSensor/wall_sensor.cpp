#include "wall_sensor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

WallSensor:: WallSensor(Adc *adc_, Iled *iled_):
    adc(adc_),
    iled(iled_),
    isIledOn(false)
{}
WallSensor::~WallSensor(){}

void WallSensor::update(){
    if(isIledOn) {
        rFront = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
        rSide  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
        lFront = adc->adcBuff[LEFT_FRONT_WSENS_CH];
        lSide  = adc->adcBuff[LEFT_SIDE_WSENS_CH];
        iled->off();
        isIledOn = false;
    }
    else {
        iled->on();
        isIledOn = true;
    }
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
