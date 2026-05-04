#include "velocity.h"

Velocity::Velocity(Accel *accel_, EncoderDistance *encDistance_) :
    accel(accel_),
    encDistance(encDistance_),
    vEncLp(0.0),
    vFused(0.0)
{
    reset();
}
Velocity::~Velocity(){}

void Velocity::init(){}

void Velocity::update() {
    // calc velocity from encoder distance
    float vEncRaw = encDistance->deltaMm / 0.5;
    vEncLp        = 0.7*vEncLp + 0.3*vEncRaw;

    // calc velocity from accelY(mm/ss -> mm/s)
    float vPred = vFused + accel->mmpss.y*0.001;

    // fusion
    vFused = 0.1*vPred + 0.9*vEncLp;
    // vFused   = vPred;

    mmps.y   = vFused;
}

void Velocity::reset() {
    mmps = {0.0, 0.0, 0.0};
}

void Velocity::dump() {
    sendMessage("[adc]@");
    sendMessage("mmps:");
    sendFloat(mmps.y);
    sendMessage(",");
    sendMessage("vEncLp:");
    sendFloat(vEncLp);
    sendMessage(", ");
    sendMessage("vFused:");
    sendFloat(vFused);
    sendMessage("\r\n");
}
