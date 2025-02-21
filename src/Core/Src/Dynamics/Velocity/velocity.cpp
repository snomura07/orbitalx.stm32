#include "velocity.h"

Velocity::Velocity(Accel *accel_) :
    accel(accel_),
    lastTime(0),
    dt(0.0)
{
    reset();
}
Velocity::~Velocity(){}

void Velocity::init(){}

void Velocity::update() {
    uint32_t now = HAL_GetTick();
    dt = (float)(now - lastTime) / 1000.0f;
    lastTime = now;

    mmps.x += accel->mmpss.x * dt;
    mmps.y += accel->mmpss.y * dt;
    mmps.z += accel->mmpss.z * dt;
}

void Velocity::reset() {
    mmps = {0.0, 0.0, 0.0};
}

void Velocity::dump() {
    sendMessage("Velocity: ");
    sendFloat(mmps.x);
    sendMessage(", ");
    sendFloat(mmps.y);
    sendMessage(", ");
    sendFloat(mmps.z);
    sendMessage("[mm/s], ");
    sendFloat(dt);
    sendMessage("\r\n");
}
