#include "dynamics_hub.h"

DynamicsHub::DynamicsHub(){}
DynamicsHub::~DynamicsHub(){}

void DynamicsHub::initDependencies(){
    angularVelocityPtr->setUsartPtr(usartPtr);
    anglePtr->setUsartPtr(usartPtr);
    accelPtr->setUsartPtr(usartPtr);
    velocityPtr->setUsartPtr(usartPtr);
    distancePtr->setUsartPtr(usartPtr);
    encDistancePtr->setUsartPtr(usartPtr);
    this->setUsartPtr(usartPtr);
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
