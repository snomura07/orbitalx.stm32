#include "feedback_controller.h"

namespace MotorController
{
FeedbackController::FeedbackController(){
    vPid.err    = 0.0f;
    vPid.errSum = 0.0f;
    vPid.preErr = 0.0f;
    wPid.err    = 0.0f;
    wPid.errSum = 0.0f;
    wPid.preErr = 0.0f;
}
FeedbackController::~FeedbackController(){}

void FeedbackController::init(DesiredVelGenerator *dVelGenerator_,
                              Velocity *velocity_,
                              AngularVelocity *angularVelocity_,
                              WallSensor *wallSensor_){
    dVelGenerator   = dVelGenerator_;
    velocity        = velocity_;
    angularVelocity = angularVelocity_;
    wallSensor      = wallSensor_;
}

void FeedbackController::update(){
    uv = calcVelocityPid();
    uw = calcAngularVelocityPid();
}

float FeedbackController::calcVelocityPid(){
    vPid.preErr  = vPid.err;
    vPid.err     = (dVelGenerator->targetVel - velocity->mmps.y);
    vPid.errSum += vPid.err;
    return 0.1*vPid.err + 0.001*vPid.errSum + 0.01*(vPid.err-vPid.preErr);
}

float FeedbackController::calcAngularVelocityPid(){
    wPid.preErr  = wPid.err;
    wPid.err     = (0.0f - angularVelocity->dps.z);
    wPid.errSum += wPid.err;
    return 0.8*wPid.err + 0.009*wPid.errSum + 0.1*(wPid.err-wPid.preErr);
}

}
