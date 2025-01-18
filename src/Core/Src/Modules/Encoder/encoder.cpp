#include "encoder.h"

Encoder::Encoder(ADC_HandleTypeDef &hadc2_):
    hadc2(&hadc2_),
    counter(0),
    currRaw(0),
    preRaw(0),
    uCnt(0),
    max(0),
    min(9999),
    currThreUP(0),
    currThreDown(0),
    THRE_UP(3845),
    THRE_DOWN(3835)
{
}
Encoder::~Encoder(){}

void Encoder::update(){
    execAdc();
}

void Encoder::execAdc(){
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
    HAL_ADC_ConfigChannel(hadc2, &sConfig);

    HAL_ADC_Start(hadc2);
    HAL_ADC_PollForConversion(hadc2, HAL_MAX_DELAY); // 変換完了待ち
    uint16_t raw = HAL_ADC_GetValue(hadc2);
    HAL_ADC_Stop(hadc2);

    preRaw  = currRaw;
    currRaw = raw;
    // ↑↓
    if (currRaw > THRE_UP && preRaw <= THRE_UP) {
        counter++;
    }
    else if (currRaw <= THRE_UP && preRaw > THRE_UP) {
        counter++;
    }

    // ↓↑
    else if (currRaw < THRE_DOWN && preRaw >= THRE_DOWN) {
        counter++;
    }
    else if (currRaw >= THRE_DOWN && preRaw < THRE_DOWN) {
        counter++;
    }


    if(currRaw > max){
        max = currRaw;
    }
    if(currRaw < min){
        min = currRaw;
    }

    uCnt++;
    if(uCnt == 100){
        if((max-min) > 10){
            currThreUP   = max - 5;
            currThreDown = min + 10;
            THRE_UP = currThreUP;
            THRE_DOWN = currThreDown;
            max  = 0;
            min  = 9999;
        }
        uCnt = 0;
    }
}

void Encoder::dump(){
    sendMessage("enc:");
    sendLong(currRaw);
    sendMessage(", ");
    sendMessage("cnt:");
    sendLong(counter);
    sendMessage(", ");
    sendMessage("max:");
    sendLong(max);
    sendMessage(", ");
    sendMessage("min:");
    sendLong(min);
    sendMessage(",");
    sendMessage("ThreUP:");
    sendLong(currThreUP);
    sendMessage(", ");
    sendMessage("ThreDown:");
    sendLong(currThreDown);
    sendMessage("\r\n");
}
