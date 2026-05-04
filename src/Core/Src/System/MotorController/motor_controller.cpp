#include "motor_controller.h"

MotorController::MotorController():
    isActive(false),
    accel(0.0),
    angularAccel(0.0),
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

void MotorController::setAngularAccel(float wa) {
    angularAccel = wa;
}

void MotorController::update() {

    // desiredVelCnt++;
    // setAccel(1000.0);

    // if(desiredVelCnt < 2000){
    //     currDesiredVelocity += accel*DELTA_T;
    //     if(currDesiredVelocity > 300.0) {
    //         currDesiredVelocity = 300.0;
    //     }
    // }
    // else if(desiredVelCnt >= 2000 && desiredVelCnt < 4000){
    //     currDesiredVelocity -= accel*DELTA_T;
    //     if(currDesiredVelocity < 0.0) {
    //         currDesiredVelocity = 0.0;
    //     }
    // }
    // else if(desiredVelCnt >= 4000){
    //     desiredVelCnt = 0;
    // }

    updateCurrDesiredVelocity();
    updateCurrDesiredAngularVelocity();

    float uV = updateVelocityPID();
    float uW = updateAngularVelocityPID();

    // float uR = 100.0f - uV - uW;
    // float uL = 100.0f - uV + uW;
    float uR = 100.0f;
    float uL = 100.0f;
    rMot->setDuty(uR);
    lMot->setDuty(uL);
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
}

void MotorController::updateCurrDesiredAngularVelocity() {
    //加速
    if(preDesiredAngularVelocity < desiredAngularVelocity){
        currDesiredAngularVelocity += angularAccel*DELTA_T;
        if(currDesiredAngularVelocity > desiredAngularVelocity) {
            currDesiredAngularVelocity = desiredAngularVelocity;
        }
    }
    //減速
    else{
        currDesiredAngularVelocity -= angularAccel*DELTA_T;
        if(currDesiredAngularVelocity < desiredAngularVelocity) {
            currDesiredAngularVelocity = desiredAngularVelocity;
        }
    }
}

float MotorController::updateVelocityPID() {
    pidVel.preErr  = pidVel.err;
    pidVel.err     = (currVel->mmps.y - currDesiredVelocity);
    pidVel.errSum += pidVel.err;
    float u        = 0.8*pidVel.err + 0.003*pidVel.errSum + 0.1*pidVel.preErr;

    setLog1((int16_t)currDesiredVelocity);
    setLog2((int16_t)currVel->mmps.y);
    setLog3((int16_t)u);

    return u;
}

float MotorController::updateAngularVelocityPID() {
    pidAngVel.preErr  = pidAngVel.err;
    pidAngVel.err     = (currAngVel->dps.z - currDesiredAngularVelocity);
    pidAngVel.errSum += pidAngVel.err;

    return (0.1*pidAngVel.err + 0.001*pidAngVel.errSum + 0.1*pidAngVel.preErr);
}

void MotorController::activate() {
    rMot->start();
    lMot->start();
    isActive = true;
}

void MotorController::deActivate() {
    rMot->setDuty(0);
    lMot->setDuty(0);
    rMot->stop();
    lMot->stop();
    isActive = false;
}

void MotorController::dump() {
    sendMessage("[adc]@");
    sendMessage("dv:");
    sendFloat(currDesiredVelocity);
    sendMessage(",vel:");
    sendFloat(currVel->mmps.y);
    sendMessage(",gyro:");
    sendFloat(currAngVel->dps.z);
    sendMessage("\r\n");
}
