#include "motor_controller.h"

MotorController::MotorController():
    isActive(false),
    accel(0.0),
    desiredVelocity(0.0),
    desiredAngularVelocity(0.0),
    currDesiredVelocity(0.0),
    currDesiredAngularVelocity(0.0),
    preDesiredVelocity(0.0),
    preDesiredAngularVelocity(0.0)
{
    pidVel    = {0.0, 0.0, 0.0};
    pidAngVel = {0.0, 0.0, 0.0};
}
MotorController::~MotorController(){}

void MotorController::init(Motor *rMot_, Motor *lMot_, Velocity *vel_, AngularVelocity *currAngVel_){
    rMot       = rMot_;
    lMot       = lMot_;
    currVel    = vel_;
    currAngVel = currAngVel_;
}

void MotorController::setDesiredVelocity(float vd) {
    preDesiredVelocity = desiredVelocity;
    desiredVelocity    = vd;
}

void MotorController::setDesiredAngularVelocity(float wd) {
    preDesiredAngularVelocity = desiredAngularVelocity;
    desiredAngularVelocity    = wd;
}

void MotorController::setAccel(float a) {
    accel = a;
}

void MotorController::update() {
    updateCurrDesiredVelocity();
    updateCurrDesiredAngularVelocity();

    float uV = updateVelocityPID();
    float uW = updateAngularVelocityPID();

    float uR = 200.0f - uW + uV;
    float uL = 200.0f + uW + uV;

}

void MotorController::updateCurrDesiredVelocity() {

    //加速
    if(preDesiredVelocity < desiredVelocity){
        currDesiredVelocity += accel*DELTA_T;
        if(currDesiredVelocity > desiredVelocity) {
            currDesiredVelocity = desiredVelocity;
        }
    }
    //減速
    else{
        currDesiredVelocity -= accel*DELTA_T;
        if(currDesiredVelocity < desiredVelocity) {
            currDesiredVelocity = desiredVelocity;
        }
    }

    sendMessage("[adc]@");
    sendFloat(currDesiredVelocity);
    sendMessage("\r\n");
}

void MotorController::updateCurrDesiredAngularVelocity() {

}

float MotorController::updateVelocityPID() {
    pidVel.preErr  = pidVel.err;
    pidVel.err     = (currVel->mmps.y - desiredVelocity);
    pidVel.errSum += pidVel.err;

    return (0.1*pidVel.err + 0.001*pidVel.errSum + 0.1*pidVel.preErr);
}

float MotorController::updateAngularVelocityPID() {
    pidAngVel.preErr  = pidAngVel.err;
    pidAngVel.err     = (currAngVel->dps.z - desiredAngularVelocity);
    pidAngVel.errSum += pidAngVel.err;

    return (0.1*pidAngVel.err + 0.001*pidAngVel.errSum + 0.1*pidAngVel.preErr);
}

void MotorController::activate() {
    rMot->start();
    lMot->start();
    isActive = true;
}

void MotorController::deActivate() {
    rMot->stop();
    lMot->stop();    
    isActive = false;
}