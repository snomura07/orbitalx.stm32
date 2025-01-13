#include "encoder.h"

Encoder::Encoder(ADC_HandleTypeDef &hadc2_):
    hadc2(&hadc2_),
    counter(0),
    inMotion(0)
{
    for(int i=0; i<WINDOW_SIZE; i++){
        encWindow[i] = 0;
    }
}
Encoder::~Encoder(){}

void Encoder::execAdc(){
    ADC_ChannelConfTypeDef sConfig = {0};

    // チャネル設定
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
    HAL_ADC_ConfigChannel(hadc2, &sConfig);

    // ADC変換を実行
    HAL_ADC_Start(hadc2);
    HAL_ADC_PollForConversion(hadc2, HAL_MAX_DELAY); // 変換完了待ち
    uint32_t value = HAL_ADC_GetValue(hadc2);
    HAL_ADC_Stop(hadc2);

    ave = 0;
    for(int i=0; i<WINDOW_SIZE-1; i++){
        encWindow[i] = encWindow[i+1];
        ave += encWindow[i];
    }
    encWindow[WINDOW_SIZE-1] = value;
    ave += value;
    ave /= WINDOW_SIZE;


    if (ave > 3830) {
        if (!inMotion) {
            counter++;
            inMotion = true;
        }
    } else {
        inMotion = false;
    }
}

void Encoder::out(){
    sendMessage("enc:");
    sendLong(ave);
    sendMessage(", ");
    sendMessage("cnt:");
    sendLong(counter);
    sendMessage("\r\n");
}
