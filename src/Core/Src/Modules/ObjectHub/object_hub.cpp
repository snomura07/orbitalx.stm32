#include "object_hub.h"
#include <Led/led.h>

ObjectHub::ObjectHub() = default;
ObjectHub::~ObjectHub() = default;

void ObjectHub::initDependencies(){
    ledBlue1Ptr->setUsart(usartPtr);
    ledBlue2Ptr->setUsart(usartPtr);
    ledGreenPtr->setUsart(usartPtr);
    ledRedPtr->setUsart(usartPtr);
    mapPtr->setUsart(usartPtr);
}
