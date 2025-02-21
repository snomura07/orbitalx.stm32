#include "object_hub.h"

ObjectHub::ObjectHub(){}
ObjectHub::~ObjectHub(){}

void ObjectHub::initDependencies(){
    ledBlueFrontPtr->setUsart(usartPtr);
    ledBlueBackPtr->setUsart(usartPtr);
    ledOrangePtr->setUsart(usartPtr);
    ledGreenPtr->setUsart(usartPtr);
    ledRedPtr->setUsart(usartPtr);
    ledDarkGreenPtr->setUsart(usartPtr);
    imuPtr->setUsart(usartPtr);
    rEncPtr->setUsart(usartPtr);
    lEncPtr->setUsart(usartPtr);
    rMotPtr->setUsart(usartPtr);
    lMotPtr->setUsart(usartPtr);
    battPtr->setUsart(usartPtr);
    wallSensPtr->setUsart(usartPtr);
    mapPtr->setUsart(usartPtr);
    timerCntPtr->setUsart(usartPtr);
    angularVelocityPtr->setUsart(usartPtr);
    anglePtr->setUsart(usartPtr);
    accelPtr->setUsart(usartPtr);
    velocityPtr->setUsart(usartPtr);
    distancePtr->setUsart(usartPtr);
}
