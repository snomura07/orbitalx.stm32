#ifndef ANGULAR_VELOCITY_H
#define ANGULAR_VELOCITY_H

#include <MasterDefine.h>
#include <UtilInterface/util_interface.h>
#include <Imu/imu.h>

class AngularVelocity : public UtilInterface{
public:
    AxisFloat dps;

public:
    AngularVelocity(Imu *imu_);
    ~AngularVelocity();
    void init();
    void update();
    void dump();

private:
    Imu *imu;
    float scale;
};

#endif
