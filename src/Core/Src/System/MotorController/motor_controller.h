#ifndef SYSTEM_MOTOR_CONTROLLER_H_
#define SYSTEM_MOTOR_CONTROLLER_H_
#include <main.h>
#include <Motor/motor.h>
#include <Velocity/velocity.h>
#include <AngularVelocity/angular_velocity.h>

#include <UsartInterface/usart_interface.h>

class MotorController : public UsartInterface{
public:
    struct PidElem {
        float err;
        float errSum;
        float preErr;
        float desired;
    };

public:
    MotorController();
    ~MotorController();
    void init(Motor *rMot_, Motor *lMot_, Velocity *vel_, AngularVelocity *currAngVel_);
    void setDesiredVelocity(float vd);
    void setDesiredAngularVelocity(float wd);
    void update();

private:
    float updateVelocityPID();
    float updateAngularVelocityPID();

private:
    Motor *rMot;
    Motor *lMot;
    Velocity *currVel;
    AngularVelocity *currAngVel;
    PidElem pidVel;
    PidElem pidAngVel;
};

#endif
