#include "battery.h"

Battery::Battery(ADC_HandleTypeDef &hadc2_):
    hadc2(&hadc2_),
    raw(0),
    volt(0.0)
{
}
Battery::~Battery(){}

void Battery::update(){
    execAdc();
    float ref = 3.0;
    volt = (float)raw/4095.0 * 2.109 * ref; // Adjusted voltage divider ratio from 2.0 to 2.109 to account for measurement errors.
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
    sendMessage("batt raw:");
    sendInt(raw);
    sendMessage(", ");
    sendMessage("batt volt:");
    sendFloat(volt);
    sendMessage("\r\n");
}
