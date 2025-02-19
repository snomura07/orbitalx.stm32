#include "battery.h"

Battery::Battery(Adc *adc_):
    adc(adc_),
    raw(0),
    volt(0.0),
    mVolt(0)
{
    memset(mVoltBuff, 3800, sizeof(mVoltBuff));
}
Battery::~Battery(){}

void Battery::update(){
    execAdc();
    float ref = 3.0;
    volt  = (float)raw/4095.0 * 2.109 * ref;

    // calc mV using ring buffer
    mVolt = 0;
    for(int i=0; i<BUFF_SIZE-1; i++){
        mVoltBuff[i] = mVoltBuff[i+1];
        mVolt += mVoltBuff[i];
    }
    mVoltBuff[BUFF_SIZE-1] = (uint16_t)(volt * 1000.0);
    mVolt += mVoltBuff[BUFF_SIZE-1];
    mVolt /= BUFF_SIZE;
}

void Battery::execAdc(){
    raw = adc->adcValues[BATTERY_CH];
}

void Battery::dump(){
    sendMessage("raw :");
    sendInt(raw);
    sendMessage(", ");
    sendMessage("batt[V] :");
    sendFloat(volt);
    sendMessage(", ");
    sendMessage("batt[mV] :");
    sendInt(mVolt);
    sendMessage("\r\n");
}
