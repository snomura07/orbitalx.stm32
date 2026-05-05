#include "led_controller.h"

LedController::LedController():
    blinkToggle(false)
{}
LedController::~LedController(){}

void LedController::init( Led *blueFront_,
                          Led *blueBack_,
                          Led *orange_,
                          Led *green_,
                          Led *red_,
                          Led *darkGreen_) {
    ledArr[LedEnum::ORANGE] = orange_;
    ledArr[LedEnum::GREEN] = green_;
    ledArr[LedEnum::BLUE_FRONT] = blueFront_;
    ledArr[LedEnum::BLUE_BACK] = blueBack_;
    ledArr[LedEnum::RED] = red_;
    ledArr[LedEnum::DARK_GREEN] = darkGreen_;
}

void LedController::turnOn(LedEnum no) {
    ledArr[no]->on();
}

void LedController::turnOff(LedEnum no) {
    ledArr[no]->off();
}

void LedController::turnOnLevel(int8_t num){
    // if(num<0 || num>LED_SIZE) return;

    // for(int i=0; i<LED_SIZE; i++){
    //     if(i == num){
    //         ledArr[i]->on();
    //     }
    //     else{
    //         ledArr[i]->off();
    //     }
    // }
}

void LedController::allOff(){
    for(int i=0; i<LedEnum::SIZE; i++){
        ledArr[i]->off();
    }
}

void LedController::allOn(){
    for(int i=0; i<LedEnum::SIZE; i++){
        ledArr[i]->on();
    }
}

void LedController::launchBlink(){
    if(blinkToggle){
        blinkToggle = !blinkToggle;
        allOff();
        ledArr[LedEnum::DARK_GREEN]->on();
        ledArr[LedEnum::RED]->on();
        HAL_Delay(80);
    }
    else {
        blinkToggle = !blinkToggle;
        allOff();
        HAL_Delay(80);
    }
}
