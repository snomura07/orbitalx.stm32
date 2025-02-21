#include "accel.h"

Accel::Accel(Imu *imu_) :
    imu(imu_)
{
    scale = imu->getAccelScale();
}
Accel::~Accel(){}

void Accel::init(){}

void Accel::update() {
    mmpss.x = (float)imu->accelCorrected.x / scale * 9806.65f;// mm/s² に変換
    mmpss.y = (float)imu->accelCorrected.y / scale * 9806.65f;
    mmpss.z = (float)imu->accelCorrected.z / scale * 9806.65f;
}

void Accel::dump() {
    sendMessage("accel: ");
    sendFloat(mmpss.x);
    sendMessage(", ");
    sendFloat(mmpss.y);
    sendMessage(", ");
    sendFloat(mmpss.z);
    sendMessage("[mm/ss]\r\n");
}
