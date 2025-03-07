#include "object_hub.h"

ObjectHub::ObjectHub(){}
ObjectHub::~ObjectHub(){}

void ObjectHub::initDependencies(){
    ledBlueFrontPtr->setUsartPtr(usartPtr);
    ledBlueBackPtr->setUsartPtr(usartPtr);
    ledOrangePtr->setUsartPtr(usartPtr);
    ledGreenPtr->setUsartPtr(usartPtr);
    ledRedPtr->setUsartPtr(usartPtr);
    ledDarkGreenPtr->setUsartPtr(usartPtr);
    imuPtr->setUsartPtr(usartPtr);
    rEncPtr->setUsartPtr(usartPtr);
    lEncPtr->setUsartPtr(usartPtr);
    rMotPtr->setUsartPtr(usartPtr);
    lMotPtr->setUsartPtr(usartPtr);
    battPtr->setUsartPtr(usartPtr);
    wallSensPtr->setUsartPtr(usartPtr);
    mapPtr->setUsartPtr(usartPtr);
    timerCntPtr->setUsartPtr(usartPtr);


}
