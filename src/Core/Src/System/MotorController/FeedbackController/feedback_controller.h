#ifndef FEEDBACK_CONTROLLER_H
#define FEEDBACK_CONTROLLER_H

#include <MotorController/DesiredVelGenerator/desired_vel_generator.h>

// dunamics, obj
#include <Velocity/velocity.h>
#include <AngularVelocity/angular_velocity.h>
#include <WallSensor/wall_sensor.h>

namespace MotorController
{
class FeedbackController {
public:
    float uv;
    float uw;

public:
    FeedbackController();
    ~FeedbackController();
    void init(DesiredVelGenerator *dVelGenerator_,
              Velocity *velocity_,
              AngularVelocity *angularVelocity_,
              WallSensor *wallSensor_);
    void update();

private:
    float calcVelocityPid();
    float calcAngularVelocityPid();

private:
    struct PidElement {
        float err;
        float errSum;
        float preErr;
    };

    DesiredVelGenerator *dVelGenerator;
    Velocity *velocity;
    AngularVelocity *angularVelocity;
    WallSensor *wallSensor;

    PidElement vPid;
    PidElement wPid;
};
}

#endif
