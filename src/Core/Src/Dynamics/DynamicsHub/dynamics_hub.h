#ifndef DYNAMICS_HUB_H
#define DYNAMICS_HUB_H

#include <Usart/usart.h>
#include <AngularVelocity/angular_velocity.h>
#include <Angle/angle.h>
#include <Accel/accel.h>
#include <Velocity/velocity.h>
#include <Distance/distance.h>
#include <EncoderDistance/encoder_distance.h>

class DynamicsHub {
public:
    DynamicsHub();
    ~DynamicsHub();

    void initDependencies();

public:
    Usart *usartPtr;
    AngularVelocity *angularVelocityPtr;
    Angle *anglePtr;
    Accel *accelPtr;
    Velocity *velocityPtr;
    Distance *distancePtr;
    EncoderDistance *encDistancePtr;
};

#endif
