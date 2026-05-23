#include "run_core.h"

RunCore::RunCore(){}
RunCore::~RunCore(){}

void RunCore::init( LedController *ledController_,
                    EncoderDistance *currDis_) {
    ledController   = ledController_;
    currDis         = currDis_;
}

void RunCore::moveForward(float dis) {

    while(1){
        sendFloat(currDis->mm);
        sendMessage("\r\n");


        if(currDis->mm > dis){
            ledController->turnOn(LedController::LedEnum::BLUE_FRONT);
            break;
        }
    }

}
