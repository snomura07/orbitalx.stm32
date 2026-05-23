#include "motor_driver.h"

namespace MotorController
{
MotorDriver::MotorDriver(){}
MotorDriver::~MotorDriver(){}

void MotorDriver::init(Motor *rMotor_, Motor *lMotor_){
    rMotor = rMotor_;
    lMotor = lMotor_;
}

void MotorDriver::enable(){
    rMotor->start();
    lMotor->start();
}

void MotorDriver::disable(){
    rMotor->stop();
    lMotor->stop();
}

void MotorDriver::setDuty(float dutyRight, float dutyLeft){

    rMotor->setDuty((uint16_t)dutyRight);
    lMotor->setDuty((uint16_t)dutyLeft);
}

}
