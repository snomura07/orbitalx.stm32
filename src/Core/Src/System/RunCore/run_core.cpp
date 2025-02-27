#include "run_core.h"

RunCore::RunCore(){}
RunCore::~RunCore(){}

void RunCore::init(MotorController *motorController_, EncoderDistance *currDis_) {
    motorController = motorController_;
    currDis         = currDis_;
}

void RunCore::moveForward(float dis) {
    motorController->setDesiredVelocity(300.0);
    motorController->setAccel(6000.0);
    motorController->setDesiredAngularVelocity(0.0);
    motorController->setAngularAccel(6000.0);
    motorController->activate();

    while(currDis->mm < dis);
    motorController->setDesiredVelocity(0.0);
    motorController->deActivate();
}
