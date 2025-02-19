#include "encoder.h"

Encoder::Encoder(Adc *adc_, ModeEnum mode_):
    adc(adc_),
    mode(mode_),
    counter(0),
    currRaw(0),
    preRaw(0),
    THRE_UP(3451),
    THRE_DOWN(2841),
    HYSTERESIS(0)
{
    memset(buff, 0, sizeof(buff));
}
Encoder::~Encoder(){}

void Encoder::update(){
    execAdc();
}

void Encoder::execAdc(){
    uint16_t raw = (mode == RIGHT) ? adc->adcValues[RIGHT_ENC_CH] : adc->adcValues[LEFT_ENC_CH];

    preRaw  = currRaw;
    currRaw = 0;
    for(int i=0; i<BUFF_SIZE-1; i++){
        buff[i]  = buff[i+1];
        currRaw += buff[i];
    }
    buff[BUFF_SIZE-1] = raw;
    currRaw += buff[BUFF_SIZE-1];
    currRaw /= BUFF_SIZE;

    // ** THRE_UP を超えた時 **
    if (preRaw <= THRE_UP - HYSTERESIS && currRaw > THRE_UP) {
        counter++;
    }
    // ** THRE_UP を下回った時 **
    else if (preRaw >= THRE_UP + HYSTERESIS && currRaw < THRE_UP) {
        counter++;
    }
    // ** THRE_DOWN を下回った時 **
    else if (preRaw >= THRE_DOWN + HYSTERESIS && currRaw < THRE_DOWN) {
        counter++;
    }
    // ** THRE_DOWN を超えた時 **
    else if (preRaw <= THRE_DOWN - HYSTERESIS && currRaw > THRE_DOWN) {
        counter++;
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
