#include "composer.h"

namespace MotorController
{
Composer::Composer():uRight(0), uLeft(0){}
Composer::~Composer(){}

void Composer::init(Battery *battery_){
    battery = battery_;
}

void Composer::compose(float fbuv, float fbuw, float ffuv){
    uRight = (ffuv + fbuv + fbuw) / battery->mVolt * DUTY_MAX;
    uLeft  = (ffuv + fbuv - fbuw) / battery->mVolt * DUTY_MAX;
}


}
