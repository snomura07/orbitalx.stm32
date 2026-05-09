#include "run_core.h"

RunCore::RunCore(){}
RunCore::~RunCore(){}

void RunCore::init( MotorController *motorController_,
                    LedController *ledController_,
                    EncoderDistance *currDis_) {
    motorController = motorController_;
    ledController   = ledController_;
    currDis         = currDis_;
}

void RunCore::moveForward(float dis) {
    motorController->setDesiredVelocity(300.0);
    motorController->setAccel(4000.0);
    motorController->setDesiredAngularVelocity(0.0);
    motorController->setAngularAccel(6000.0);
    motorController->activate();

    while(1){
        sendFloat(currDis->mm);
        sendMessage("\r\n");


        if(currDis->mm > dis){
            ledController->turnOn(LedController::LedEnum::BLUE_FRONT);
            break;
        }
    }

    // HAL_Delay(800);
    motorController->setDesiredVelocity(0.0);

    HAL_Delay(500);
    motorController->deActivate();
}
