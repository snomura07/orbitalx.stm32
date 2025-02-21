#ifndef ACCEL_H
#define ACCEL_H

#include <MasterDefine.h>
#include <UsartInterface/usart_interface.h>
#include <Imu/imu.h>

class Accel : public UsartInterface{
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
