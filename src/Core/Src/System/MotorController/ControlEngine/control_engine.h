#ifndef CONTROL_ENGINE_H
#define CONTROL_ENGINE_H
#include <UtilInterface/util_interface.h>
#include <MotorController/DesiredVelGenerator/desired_vel_generator.h>
#include <MotorController/FeedbackController/feedback_controller.h>
#include <MotorController/FeedforwardController/feedforward_controller.h>
#include <MotorController/Composer/composer.h>
#include <MotorController/MotorDriver/motor_driver.h>

// dynamics
#include <Velocity/velocity.h>
#include <AngularVelocity/angular_velocity.h>

// obj
#include <WallSensor/wall_sensor.h>

namespace MotorController
{
class ControlEngine : public UtilInterface{
public:
    ControlEngine();
    ~ControlEngine();

    void init(DesiredVelGenerator *dVelGenerator_,
              FeedbackController *fbController_,
              FeedforwardController *ffController_,
              Composer *composer_,
              MotorDriver *motorDriver_);
    void setTarget(float accel, float desiredVel);
    void update();
    void activate();
    void deactivate();
    void dump();

private:
    DesiredVelGenerator *dVelGenerator;
    FeedbackController *fbController;
    FeedforwardController *ffController;
    Composer *composer;
    MotorDriver *motorDriver;
};
}

#endif
