#include "control_engine.h"

namespace MotorController
{
ControlEngine::ControlEngine(){}
ControlEngine::~ControlEngine(){}
void ControlEngine::init(DesiredVelGenerator *dVelGenerator_,
                            FeedbackController *fbController_,
                            FeedforwardController *ffController_,
                            Composer *composer_,
                            MotorDriver *motorDriver_){
    dVelGenerator = dVelGenerator_;
    fbController  = fbController_;
    ffController  = ffController_;
    composer      = composer_;
    motorDriver   = motorDriver_;
}

void ControlEngine::setTarget(float accel, float desiredVel){
    dVelGenerator->setTarget(accel, desiredVel);
}

void ControlEngine::update(){
    dVelGenerator->update();

    fbController->update();

    ffController->update();

    composer->compose(fbController->uv, fbController->uw, ffController->uv);

    motorDriver->setDuty(composer->uRight, composer->uLeft);
}

void ControlEngine::activate(){
    motorDriver->enable();
}

void ControlEngine::deactivate(){
    motorDriver->disable();
}

void ControlEngine::dump(){
    sendMessage("target vel: ");
    sendFloat(dVelGenerator->targetVel);
    sendMessage("\r\n");

    sendMessage("fbuv: ");
    sendFloat(fbController->uv);
    sendMessage("\r\n");

    sendMessage("fbuw: ");
    sendFloat(fbController->uw);
    sendMessage("\r\n");
}
}
