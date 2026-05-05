#include "battery.h"

Battery::Battery(Adc *adc_):
    adc(adc_),
    raw(0),
    volt(0.0f),
    mVolt(0),
    mVoltRaw(0),
    mVoltRawSum(0),
    latestIndex(0)
{
    for (int i = 0; i < BUFF_SIZE; i++) {
        mVoltBuff[i] = 3800;
        mVoltRawSum += mVoltBuff[i];
    }
}
Battery::~Battery(){}

void Battery::update(){
    execAdc();
    constexpr float ref = 3.0f;
    volt     = static_cast<float>(raw) / 4095.0f * 2.109f * ref;
    mVoltRaw = static_cast<uint16_t>(volt * 1000.0f);

    mVoltRawSum -= mVoltBuff[latestIndex];
    mVoltRawSum += mVoltRaw;
    mVoltBuff[latestIndex] = mVoltRaw;
    mVolt = static_cast<uint16_t>(mVoltRawSum / BUFF_SIZE);

    latestIndex++;
    if(latestIndex == BUFF_SIZE){
        latestIndex = 0;
    }
}

void Battery::execAdc(){
    raw = adc->adcBuff[BATTERY_CH];
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
