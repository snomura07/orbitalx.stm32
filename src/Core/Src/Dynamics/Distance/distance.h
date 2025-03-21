#ifndef DISTANCE_H
#define DISTANCE_H

#include <MasterDefine.h>
#include <UtilInterface/util_interface.h>
#include <Velocity/velocity.h>

class Distance : public UtilInterface{
public:
    AxisFloat mm;

public:
    Distance(Velocity *velocity_);
    ~Distance();
    void init();
    void update();
    void reset();
    void dump();

private:
    Velocity *velocity;
    uint32_t lastTime;
    float dt;
};

#endif
