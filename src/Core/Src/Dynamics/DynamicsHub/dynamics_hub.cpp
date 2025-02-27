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
}
