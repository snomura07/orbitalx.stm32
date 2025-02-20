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
    rFront.on = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
    rSide.on  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
    lFront.on = adc->adcBuff[LEFT_FRONT_WSENS_CH];
    lSide.on  = adc->adcBuff[LEFT_SIDE_WSENS_CH];

    rFront.filtered = rFront.on;
    rSide.filtered  = rSide.on ;
    lFront.filtered = lFront.on;
    lSide.filtered  = lSide.on ;

    iled->on(); // OFFはadc側
}

void WallSensor::dump(){
    sendMessage("rFront:");
    sendInt(rFront.filtered);
    sendMessage(", ");
    sendMessage("rSide:");
    sendInt(rSide.filtered);
    sendMessage(", ");
    sendMessage("lFront:");
    sendInt(lFront.filtered);
    sendMessage(", ");
    sendMessage("lSide:");
    sendInt(lSide.filtered);
    sendMessage("\r\n");
}
