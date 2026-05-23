#ifndef DESIRED_VEL_GENERATOR_H
#define DESIRED_VEL_GENERATOR_H
#include <MasterDefine.h>

namespace MotorController
{
class DesiredVelGenerator {
public:
    DesiredVelGenerator();
    ~DesiredVelGenerator();
    void setTarget(float accel_, float desiredVel_);
    void update();

public:
    float targetVel;

private:
    float accel;
    float preDesiredVel;
    float desiredVel;
};
}

#endif
