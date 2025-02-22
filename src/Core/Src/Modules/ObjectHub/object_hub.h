#ifndef OBJECT_HUB_H
#define OBJECT_HUB_H

#include <memory>
#include <Led/led.h>
#include <Map/map.h>
#include <Imu/imu.h>
#include <Motor/motor.h>
#include <Encoder/encoder.h>
#include <Battery/battery.h>
#include <WallSensor/wall_sensor.h>
#include <Iled/i_led.h>
#include <TimerCount/timer_count.h>
#include <Usart/usart.h>
#include <Adc/adc.h>
#include <AngularVelocity/angular_velocity.h>
#include <Angle/angle.h>
#include <Accel/accel.h>
#include <Velocity/velocity.h>
#include <Distance/distance.h>
#include <EncoderDistance/encoder_distance.h>

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
    Led *ledRedPtr;
    Led *ledDarkGreenPtr;
    Imu *imuPtr;
    Encoder *rEncPtr;
    Encoder *lEncPtr;
    Motor *rMotPtr;
    Motor *lMotPtr;
    Battery *battPtr;
    WallSensor *wallSensPtr;
    Iled *iledPtr;
    Map *mapPtr;
    TimerCount *timerCntPtr;
    Usart *usartPtr;
    Adc *adcPtr;
    AngularVelocity *angularVelocityPtr;
    Angle *anglePtr;
    Accel *accelPtr;
    Velocity *velocityPtr;
    Distance *distancePtr;
    EncoderDistance *encDistancePtr;
};

#endif
