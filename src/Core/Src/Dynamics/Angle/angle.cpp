#include "angle.h"

Angle::Angle(AngularVelocity *angularVelocity_) :
    angularVelocity(angularVelocity_),
    deg(0.0),
    lastTime(0),
    dt(0.0)
{}
Angle::~Angle(){}

void Angle::init(){}

void Angle::update() {
    uint32_t now = HAL_GetTick();
    dt = (float)(now - lastTime) / 1000.0f;
    lastTime = now;

    deg += angularVelocity->dps.z * dt;
}

void Angle::reset() {
    deg = 0.0;
}

void Angle::dump() {
    sendMessage("Angle: ");
    sendFloat(deg);
    sendMessage("[deg], ");
    sendFloat(dt);
    sendMessage("\r\n");
}
