#ifndef VELOCITY_H
#define VELOCITY_H

#include <MasterDefine.h>
#include <UsartInterface/usart_interface.h>
#include <Accel/accel.h>

class Velocity : public UsartInterface{
public:
    AxisFloat mmps;

public:
    Velocity(Accel *accel_);
    ~Velocity();
    void init();
    void update();
    void reset();
    void dump();

private:
    Accel *accel;
    uint32_t lastTime;
    float dt;
};

#endif
