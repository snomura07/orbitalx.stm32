#ifndef OBJECT_HUB_H
#define OBJECT_HUB_H

#include <memory>
#include <Led/led.h>
#include <Map/map.h>
#include <Imu/imu.h>
#include <Motor/motor.h>
#include <Encoder/encoder.h>
#include <Battery/battery.h>
#include <Usart/usart.h>

class ObjectHub {
public:
    ObjectHub();
    ~ObjectHub();

    void initDependencies();

public:
    Led *ledBlueFrontPtr;
    Led *ledBlueBackPtr;
    Led *ledOrangePtr;
    Led *ledGreenPtr;
    Imu *imuPtr;
    Encoder *encPtr;
    Motor *rMotPtr;
    Motor *lMotPtr;
    Battery *battPtr;
    Map *mapPtr;
    Usart *usartPtr;
};

#endif
