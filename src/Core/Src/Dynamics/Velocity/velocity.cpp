#include "velocity.h"

Velocity::Velocity(Accel *accel_, EncoderDistance *encDistance_) :
    accel(accel_),
    encDistance(encDistance_),
    lastTime(0),
    dt(0.0),
    lastDistance(0.0)
{
    reset();
}
Velocity::~Velocity(){}

void Velocity::init(){}

void Velocity::update() {
    uint32_t now = HAL_GetTick();
    dt = (float)(now - lastTime) / 1000.0f;

    mmps.x += accel->mmpss.x * dt;
    // mmps.y += accel->mmpss.y * dt;
    mmps.z += accel->mmpss.z * dt;

    if(dt > 0.01){
        float vc     = (float)(encDistance->mm - lastDistance) / dt;
        mmps.y       = 0.9*mmps.y + 0.1*vc;
        lastDistance = encDistance->mm;
        lastTime     = now;
    }
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
