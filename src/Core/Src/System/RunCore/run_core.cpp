#include "run_core.h"

RunCore::RunCore(){}
RunCore::~RunCore(){}

void RunCore::init(MotorController *motorController_, Distance *currDis_) {
    motorController = motorController_;
    currDis         = currDis_;
}

void RunCore::moveForward(float dis) {
    motorController->setDesiredVelocity(300.0);
    motorController->setDesiredAngularVelocity(0.0);

    while(currDis->mm < dis);
}
