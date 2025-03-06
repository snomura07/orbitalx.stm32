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

    // mmps.x += accel->mmpss.x * dt;
    // mmps.y += accel->mmpss.y * dt;
    // mmps.z += accel->mmpss.z * dt;

    float vc     = (encDistance->mm - lastDistance) / dt;
    mmps.y       = 0.95*mmps.y + 0.05*vc;
    lastDistance = encDistance->mm;
    lastTime     = now;
}

void Velocity::reset() {
    mmps = {0.0, 0.0, 0.0};
}

void Velocity::dump() {
    sendMessage("Velocity: ");
    sendFloat(mmps.y);
    sendMessage(", ");
    sendMessage("encDis: ");
    sendFloat(encDistance->mm);
    sendMessage(", ");
    sendFloat(lastDistance);
    sendMessage(", ");
    sendFloat(dt);
    sendMessage("\r\n");
}
