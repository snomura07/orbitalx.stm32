#ifndef SYSTEM_MOTOR_CONTROLLER_H_
#define SYSTEM_MOTOR_CONTROLLER_H_
#include <main.h>
#include <Motor/motor.h>
#include <Velocity/velocity.h>
#include <AngularVelocity/angular_velocity.h>

#include <UtilInterface/util_interface.h>

class MotorController : public UtilInterface{
public:
    struct PidElem {
        float err;
        float errSum;
        float preErr;
    };

public:
    MotorController();
    ~MotorController();
    void init(Motor *rMot_, Motor *lMot_, Velocity *vel_, AngularVelocity *currAngVel_);
    void setDesiredVelocity(float vd);
    void setDesiredAngularVelocity(float wd);
    void setAccel(float a);
    void setAngularAccel(float wa);
    void update();
    void activate();
    void deActivate();

private:
    void updateCurrDesiredVelocity();
    void updateCurrDesiredAngularVelocity();
    float updateVelocityPID();
    float updateAngularVelocityPID();

private:
    Motor *rMot;
    Motor *lMot;
    Velocity *currVel;
    AngularVelocity *currAngVel;
    PidElem pidVel;
    PidElem pidAngVel;
    float desiredVelocity;
    float desiredAngularVelocity;
    float preDesiredVelocity;
    float preDesiredAngularVelocity;
    float accel;                        // mm/ss
    float angularAccel;                 // deg/ss
    float currDesiredVelocity;          // mm/s
    float currDesiredAngularVelocity;   // deg/s
    bool isActive;
};

#endif
