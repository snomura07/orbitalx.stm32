#include "motor_controller.h"

MotorController::MotorController(){
    pidVel    = {0.0, 0.0, 0.0, 0.0};
    pidAngVel = {0.0, 0.0, 0.0, 0.0};
}
MotorController::~MotorController(){}

void MotorController::init(Motor *rMot_, Motor *lMot_, Velocity *vel_, AngularVelocity *currAngVel_){
    rMot       = rMot_;
    lMot       = lMot_;
    currVel    = vel_;
    currAngVel = currAngVel_;
}

void MotorController::setDesiredVelocity(float vd) {
    pidVel.desired = vd;
}

void MotorController::setDesiredAngularVelocity(float wd) {
    pidAngVel.desired = wd;
}

void MotorController::update() {
    float uV = updateVelocityPID();
    float uW = updateAngularVelocityPID();

    float uR = 200.0f - uW + uV;
    float uL = 200.0f + uW + uV;

}

float MotorController::updateVelocityPID() {
    pidVel.preErr  = pidVel.err;
    pidVel.err     = (currVel->mmps.y - pidVel.desired);
    pidVel.errSum += pidVel.err;

    return (0.1*pidVel.err + 0.001*pidVel.errSum + 0.1*pidVel.preErr);
}

float MotorController::updateAngularVelocityPID() {
    pidAngVel.preErr  = pidAngVel.err;
    pidAngVel.err     = (currAngVel->dps.z - pidAngVel.desired);
    pidAngVel.errSum += pidAngVel.err;

    return (0.1*pidAngVel.err + 0.001*pidAngVel.errSum + 0.1*pidAngVel.preErr);
}
