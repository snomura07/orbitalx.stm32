#ifndef OBJECT_HUB_H
#define OBJECT_HUB_H

#include <memory>
#include <Led/led.h>
#include <Map/map.h>
#include <Imu/imu.h>
#include <Usart/usart.h>

class ObjectHub {
public:
    ObjectHub();
    ~ObjectHub();

    void initDependencies();

public:
    std::shared_ptr<Led> ledBlue1Ptr;
    std::shared_ptr<Led> ledBlue2Ptr;
    std::shared_ptr<Led> ledOrangePtr;
    std::shared_ptr<Led> ledGreenPtr;
    std::shared_ptr<Imu> imuPtr;
    std::shared_ptr<Map> mapPtr;
    std::shared_ptr<Usart> usartPtr;
};

#endif
