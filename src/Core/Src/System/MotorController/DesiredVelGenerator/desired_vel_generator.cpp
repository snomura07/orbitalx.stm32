#include "desired_vel_generator.h"

namespace MotorController
{
DesiredVelGenerator::DesiredVelGenerator():
    preDesiredVel(0.0f),
    targetVel(0.0f)
{}
DesiredVelGenerator::~DesiredVelGenerator(){}

void DesiredVelGenerator::setTarget(float accel_, float desiredVel_){
    preDesiredVel = desiredVel;
    accel         = accel_;
    desiredVel    = desiredVel_;
}

void DesiredVelGenerator::update(){

    //加速
    if(preDesiredVel < desiredVel){
        targetVel += accel*DELTA_T;
        if(targetVel > desiredVel) {
            targetVel = desiredVel;
        }
    }
    //減速
    else{
        targetVel -= accel*DELTA_T;
        if(targetVel < desiredVel) {
            targetVel = desiredVel;
        }
    }
}



}
