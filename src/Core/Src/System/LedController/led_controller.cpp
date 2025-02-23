#include "led_controller.h"

LedController::LedController() {}
LedController::~LedController(){}

void LedController::init(Led *led0_, Led *led1_, Led *led2_, Led *led3_, Led *led4_, Led *led5_) {
    ledArr[0] = led0_;
    ledArr[1] = led1_;
    ledArr[2] = led2_;
    ledArr[3] = led3_;
    ledArr[4] = led4_;
    ledArr[5] = led5_;
}

void LedController::on(int8_t num){
    if(num<1 || num>LED_SIZE) return;

    for(int i=0; i<LED_SIZE; i++){
        if(i == num-1){
            ledArr[i]->on();
        }
        else{
            ledArr[i]->off();
        }
    }
}

void LedController::allOff(){
    for(int i=0; i<LED_SIZE; i++){
        ledArr[i]->off();
    }
}

void LedController::allOn(){
    for(int i=0; i<LED_SIZE; i++){
        ledArr[i]->on();
    }
}
