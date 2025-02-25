#ifndef SYSTEM_RUN_CORE_H_
#define SYSTEM_RUN_CORE_H_
#include <main.h>
#include <MotorController/motor_controller.h>
#include <Distance/distance.h>

class RunCore {
public:
    RunCore();
    ~RunCore();
    void init(MotorController *motorController_, Distance *currDis_);
    void setVelocity(float vel);
    void moveForward(float dis);
    void spinTurn();

private:
    MotorController *motorController;
    Distance *currDis;
};

#endif
