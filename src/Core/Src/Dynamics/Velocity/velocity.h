#ifndef VELOCITY_H
#define VELOCITY_H

#include <MasterDefine.h>
#include <UtilInterface/util_interface.h>
#include <Accel/accel.h>
#include <EncoderDistance/encoder_distance.h>

class Velocity : public UtilInterface{
public:
    AxisFloat mmps;

public:
    Velocity(Accel *accel_, EncoderDistance *encDistance_);
    ~Velocity();
    void init();
    void update();
    void reset();
    void dump();

private:
    Accel *accel;
    EncoderDistance *encDistance;
    uint32_t lastTime;
    float dt;
    float lastDistance;
};

#endif
