#include "velocity.h"

Velocity::Velocity(Accel *accel_, EncoderDistance *encDistance_) :
    accel(accel_),
    encDistance(encDistance_),
    lastTime(0),
    dt(0.0),
    vEncLp(0.0),
    vFused(0.0),
    lastDistance(0.0)
{
    reset();
}
Velocity::~Velocity(){}

void Velocity::init(){}

void Velocity::update() {
    uint32_t now = HAL_GetTick();
    dt = (float)(now - lastTime) / 1000.0f;

    // calc velocity from encoder distance
    float vEncRaw = (encDistance->mm - lastDistance) / dt;
    // vEncLp        = 0.7*vEncLp + 0.3*vEncRaw;
    vEncLp        = vEncRaw;

    // calc velocity from accelY(mm/ss -> mm/s)
    // float vPred = vFused + accel->mmpss.y*dt;
    float vPred = accel->mmpss.y;

    // fusion
    // vFused = 0.3*vPred + 0.7*vEncLp;
    vFused = vPred;
    mmps.y = vFused;

    lastDistance  = encDistance->mm;
    lastTime      = now;
}

void Velocity::reset() {
    mmps = {0.0, 0.0, 0.0};
}

void Velocity::dump() {
    sendMessage("Velocity: ");
    sendFloat(mmps.y);
    sendMessage(", ");
    sendFloat(vEncLp);
    sendMessage(", ");
    sendFloat(vFused);
    sendMessage(", ");
    sendFloat(encDistance->mm);
    sendMessage(", ");
    sendFloat(dt);
    sendMessage("\r\n");
}
