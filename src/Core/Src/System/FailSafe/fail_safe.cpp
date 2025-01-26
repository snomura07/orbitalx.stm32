#include "fail_safe.h"

FailSafe::FailSafe():
    emStopFlag(false)
{}
FailSafe::~FailSafe(){}

void FailSafe::update(){
    batteryCheck();
}

void FailSafe::batteryCheck(){
    if(objHub->battPtr->volt < BATTERY_THRE){
        emStopFlag = true;
    }
}

void FailSafe::emStopCheck(){
    if(emStopFlag){
        objHub->ledBlueFrontPtr->off();
        objHub->ledBlueBackPtr->off();
        objHub->ledOrangePtr->off();
        objHub->ledGreenPtr->off();
        objHub->rMotPtr->stop();
        objHub->lMotPtr->stop();
        timer15->stop();
        timer6 ->stop();
        while(1){
            objHub->ledOrangePtr->toggle();
            HAL_Delay(100);
        }
    }
}
