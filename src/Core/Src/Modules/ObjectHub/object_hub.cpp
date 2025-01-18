#include "object_hub.h"
#include <Led/led.h>

ObjectHub::ObjectHub() = default;
ObjectHub::~ObjectHub() = default;

void ObjectHub::initDependencies(){
    ledBlue1Ptr->setUsart(usartPtr);
    ledBlue2Ptr->setUsart(usartPtr);
    ledOrangePtr->setUsart(usartPtr);
    ledGreenPtr->setUsart(usartPtr);
    imuPtr->setUsart(usartPtr);
    encPtr->setUsart(usartPtr);
    rMotPtr->setUsart(usartPtr);
    lMotPtr->setUsart(usartPtr);
    battPtr->setUsart(usartPtr);
    mapPtr->setUsart(usartPtr);
}
