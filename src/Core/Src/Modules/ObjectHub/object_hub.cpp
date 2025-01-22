#include "object_hub.h"

ObjectHub::ObjectHub(){}
ObjectHub::~ObjectHub(){}

void ObjectHub::initDependencies(){
    ledBlueFrontPtr->setUsart(usartPtr);
    ledBlueBackPtr->setUsart(usartPtr);
    ledOrangePtr->setUsart(usartPtr);
    ledGreenPtr->setUsart(usartPtr);
    imuPtr->setUsart(usartPtr);
    encPtr->setUsart(usartPtr);
    rMotPtr->setUsart(usartPtr);
    lMotPtr->setUsart(usartPtr);
    battPtr->setUsart(usartPtr);
    wallSensPtr->setUsart(usartPtr);
    mapPtr->setUsart(usartPtr);
}
