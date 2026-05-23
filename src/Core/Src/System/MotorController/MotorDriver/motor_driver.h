#ifndef MotorDriver_H
#define MotorDriver_H
#include <Motor/motor.h>

namespace MotorController
{
class MotorDriver {
public:
    MotorDriver();
    ~MotorDriver();
    void init(Motor *rMotor_, Motor *lMotor_);
    void enable();
    void disable();
    void setDuty(float dutyRight, float dutyLeft);

private:
    Motor *rMotor;
    Motor *lMotor;
};
}

#endif
