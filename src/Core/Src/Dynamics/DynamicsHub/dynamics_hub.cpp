#include "dynamics_hub.h"

DynamicsHub::DynamicsHub(){}
DynamicsHub::~DynamicsHub(){}

void DynamicsHub::initDependencies(){
    angularVelocityPtr->setUsart(usartPtr);
    anglePtr->setUsart(usartPtr);
    accelPtr->setUsart(usartPtr);
    velocityPtr->setUsart(usartPtr);
    distancePtr->setUsart(usartPtr);
    encDistancePtr->setUsart(usartPtr);
    this->setUsart(usartPtr);
}

void DynamicsHub::dump() {
    sendMessage("[adc]@");
    sendMessage("angVel:");
    sendFloat(angularVelocityPtr->dps.z);
    sendMessage(",");
    sendMessage("angle:");
    sendFloat(anglePtr->deg);
    sendMessage(",");
    sendMessage("vel:");
    sendFloat(velocityPtr->mmps.y);
    sendMessage(",");
    sendMessage("encDis:");
    sendFloat(encDistancePtr->mm);
    sendMessage("\r\n");
}
