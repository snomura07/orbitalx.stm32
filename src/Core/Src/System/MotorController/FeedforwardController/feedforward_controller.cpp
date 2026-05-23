#include "feedforward_controller.h"

namespace MotorController
{
FeedforwardController::FeedforwardController():uv(0.0f){}
FeedforwardController::~FeedforwardController(){}

void FeedforwardController::init(DesiredVelGenerator *dVelGenerator_){
    dVelGenerator = dVelGenerator_;
}

void FeedforwardController::update(){
    uv = 0.588*dVelGenerator->targetVel + 53.5;
}
}
