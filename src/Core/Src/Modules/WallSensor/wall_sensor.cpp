#include "wall_sensor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

WallSensor:: WallSensor(Adc *adc_, Iled *iled_):
    adc(adc_),
    iled(iled_),
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
            rawDataOff.rFront = adc->adcBuff[RIGHT_FRONT_WSENS_CH];
            rawDataOff.rSide  = adc->adcBuff[RIGHT_SIDE_WSENS_CH];
            rawDataOff.lFront = adc->adcBuff[LEFT_FRONT_WSENS_CH];
            rawDataOff.lSide  = adc->adcBuff[LEFT_SIDE_WSENS_CH];

            iled->on();
            phase = SamplePhase::SAMPLE_ON_COMPUTE;
            break;

        case SamplePhase::SAMPLE_ON_COMPUTE: {
            const pos rawDataOn = {
                adc->adcBuff[RIGHT_FRONT_WSENS_CH],
                adc->adcBuff[RIGHT_SIDE_WSENS_CH],
                adc->adcBuff[LEFT_FRONT_WSENS_CH],
                adc->adcBuff[LEFT_SIDE_WSENS_CH]
            };

            rawData.rFront = static_cast<uint16_t>(rawDataOn.rFront - rawDataOff.rFront);
            rawData.rSide  = static_cast<uint16_t>(rawDataOn.rSide  - rawDataOff.rSide);
            rawData.lFront = static_cast<uint16_t>(rawDataOn.lFront - rawDataOff.lFront);
            rawData.lSide  = static_cast<uint16_t>(rawDataOn.lSide  - rawDataOff.lSide);

            float ratio    = (float)rawData.rSide / (paramPtr->wallSensorRefRight[2]+paramPtr->wallSensorRefLeft[2])/2;
            normData.rSide = ratio * 3000.0f;

            ratio          = (float)rawData.lSide / (paramPtr->wallSensorRefRight[3]+paramPtr->wallSensorRefLeft[3])/2;
            normData.lSide = ratio * 3000.0f;

            iled->off();
            phase = SamplePhase::SAMPLE_OFF_SET_ON;
            break;
        }
    }
}

uint16_t WallSensor::rFrontDetected() {
    return rawData.rFront > 1200 ? 1 : 0;
}

void WallSensor::dump(){
    sendMessage("rFront:");
    sendInt(rawData.rFront);
    sendMessage(", ");
    sendMessage("rSide:");
    sendInt(rawData.rSide);
    sendMessage(", ");
    sendMessage("lFront:");
    sendInt(rawData.lFront);
    sendMessage(", ");
    sendMessage("lSide:");
    sendInt(rawData.lSide);
    sendMessage(", ");
    sendMessage("rSideNorm:");
    sendInt(normData.rSide);
    sendMessage(", ");
    sendMessage("lSideNorm:");
    sendInt(normData.lSide);
    sendMessage("\r\n");
}
