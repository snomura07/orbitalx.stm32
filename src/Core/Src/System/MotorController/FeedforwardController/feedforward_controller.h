#ifndef FEEDFORWARD_CONTROLLER_H
#define FEEDFORWARD_CONTROLLER_H
#include <MotorController/DesiredVelGenerator/desired_vel_generator.h>

namespace MotorController
{
class FeedforwardController {
public:
    float uv;

public:
    FeedforwardController();
    ~FeedforwardController();
    void init(DesiredVelGenerator *dVelGenerator_);
    void update();

private:
    DesiredVelGenerator *dVelGenerator;
};
}

#endif
