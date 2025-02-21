#ifndef ANGLE_H
#define ANGLE_H

#include <MasterDefine.h>
#include <UsartInterface/usart_interface.h>
#include <AngularVelocity/angular_velocity.h>

class Angle : public UsartInterface{
public:
    float deg; //yawのみ

public:
    Angle(AngularVelocity *angularVelocity_);
    ~Angle();
    void init();
    void update();
    void reset();
    void dump();

private:
    AngularVelocity *angularVelocity;
    uint32_t lastTime;
    float dt;
};

#endif
