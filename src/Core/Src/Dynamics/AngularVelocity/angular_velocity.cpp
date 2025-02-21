#include "angular_velocity.h"

AngularVelocity::AngularVelocity(Imu *imu_) :
    imu(imu_)
{
    scale = imu->getGyroScale();
}
AngularVelocity::~AngularVelocity(){}

void AngularVelocity::init(){}

void AngularVelocity::update() {
    dps.x = (float)imu->gyroCorrected.x / scale;
    dps.y = (float)imu->gyroCorrected.y / scale;
    dps.z = (float)imu->gyroCorrected.z / scale;
}

void AngularVelocity::dump() {
    sendMessage("omega: ");
    sendFloat(dps.x);
    sendMessage(", ");
    sendFloat(dps.y);
    sendMessage(", ");
    sendFloat(dps.z);
    sendMessage("[dps]\r\n");
}
