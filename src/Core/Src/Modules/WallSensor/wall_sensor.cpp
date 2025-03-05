#include "wall_sensor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

WallSensor:: WallSensor(Adc *adc_, Iled *iled_):
    adc(adc_),
    iled(iled_),
    rFront(0),
    rSide(0),
    lFront(0),
    lSide(0)
{}
WallSensor::~WallSensor(){}

void WallSensor::update(){
    iled->on();
    rFront = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
    rSide  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
    lFront = adc->adcBuff[LEFT_FRONT_WSENS_CH];
    lSide  = adc->adcBuff[LEFT_SIDE_WSENS_CH];
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
