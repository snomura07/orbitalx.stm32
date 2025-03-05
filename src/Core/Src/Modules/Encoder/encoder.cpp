#include "encoder.h"

Encoder::Encoder(Adc *adc_, ModeEnum mode_):
    adc(adc_),
    mode(mode_),
    counter(0),
    currRaw(0),
    preRaw(0),
    upTriggered(false),
    downTriggered(false),
    staticCounter(0),
    lastCheckedValue(0),
    staticThreshold(0)
{
    memset(buff, 0, sizeof(buff));
    if(mode == RIGHT){
        THRE_UP   = 3600;
        THRE_DOWN = 3200;
        staticThreshold = 50;
    }
    else {
        THRE_UP   = 2050;
        THRE_DOWN = 1950;
        staticThreshold = 50;
    }
}
Encoder::~Encoder(){}

void Encoder::update(){
    execAdc();
}

void Encoder::execAdc(){
    uint16_t* encBuff   = (mode == RIGHT) ? adc->rightEncBuff : adc->leftEncBuff;
    int dataCount       = (mode == RIGHT) ? adc->rightEncDataCount : adc->leftEncDataCount;

    // **バッファの最新値を取得**
    int latestIndex = (dataCount > 0) ? dataCount - 1 : 0;
    uint16_t latestValue = encBuff[latestIndex];

    // **一定回数前の値と比較**
    if (abs(latestValue - lastCheckedValue) < staticThreshold) {
        staticCounter++;
    } else {
        staticCounter = 0;
    }

    lastCheckedValue = latestValue;

    // **50回（約50ms）以上ほぼ同じなら静止と判断**
    if (staticCounter >= 50){
        return;
    }

    for (int i = 0; i < dataCount; i++) {
        preRaw  = currRaw;
        currRaw = encBuff[i];

        // **通常のカウント処理**
        if (!upTriggered && preRaw <= THRE_UP && currRaw > THRE_UP) {
            counter++;
            upTriggered = true;
            downTriggered = false;
        }
        else if (!downTriggered && preRaw >= THRE_DOWN && currRaw < THRE_DOWN) {
            counter++;
            downTriggered = true;
            upTriggered = false;
        }

        // **リセット処理**
        if (upTriggered && currRaw < THRE_DOWN - 100) {
            upTriggered = false;
        }
        if (downTriggered && currRaw > THRE_UP + 100) {
            downTriggered = false;
        }
    }
}

void Encoder::dump(){
    sendMessage("enc:");
    sendLong(currRaw);
    sendMessage(", ");
    sendMessage("cnt:");
    sendLong(counter);
    sendMessage(", ");
    sendMessage("ThreUP:");
    sendLong(THRE_UP);
    sendMessage(", ");
    sendMessage("ThreDown:");
    sendLong(THRE_DOWN);
    sendMessage("\r\n");
}
