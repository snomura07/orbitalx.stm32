#ifndef ACCEL_H
#define ACCEL_H

#include <MasterDefine.h>
#include <UtilInterface/util_interface.h>
#include <Imu/imu.h>

class Accel : public UtilInterface{
public:
    AxisFloat mmpss;

public:
    Accel(Imu *imu_);
    ~Accel();
    void init();
    void update();
    void dump();

private:
    Imu *imu;
    float scale;
};

#endif
