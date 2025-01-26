#include "battery.h"

Battery::Battery(ADC_HandleTypeDef &hadc2_):
    hadc2(&hadc2_),
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
    volt  = (float)raw/4095.0 * 2.109 * ref; // Adjusted voltage divider ratio from 2.0 to 2.109 to account for measurement errors.

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
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
    HAL_ADC_ConfigChannel(hadc2, &sConfig);

    HAL_ADC_Start(hadc2);
    HAL_ADC_PollForConversion(hadc2, HAL_MAX_DELAY); // 変換完了待ち
    raw = HAL_ADC_GetValue(hadc2);
    HAL_ADC_Stop(hadc2);
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
