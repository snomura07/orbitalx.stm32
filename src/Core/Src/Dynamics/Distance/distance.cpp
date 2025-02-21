#include "distance.h"

Distance::Distance(Velocity *velocity_) :
    velocity(velocity_),
    lastTime(0),
    dt(0.0)
{
    reset();
}
Distance::~Distance(){}

void Distance::init(){}

void Distance::update() {
    uint32_t now = HAL_GetTick();
    dt = (float)(now - lastTime) / 1000.0f;
    lastTime = now;

    mm.x += velocity->mmps.x * dt;
    mm.y += velocity->mmps.y * dt;
    mm.z += velocity->mmps.z * dt;
}

void Distance::reset() {
    mm = {0.0, 0.0, 0.0};
}

void Distance::dump() {
    sendMessage("Distance: ");
    sendFloat(mm.x);
    sendMessage(", ");
    sendFloat(mm.y);
    sendMessage(", ");
    sendFloat(mm.z);
    sendMessage("[mm], ");
    sendFloat(dt);
    sendMessage("\r\n");
}
