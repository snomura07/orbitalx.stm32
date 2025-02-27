#ifndef SYSTEM_RUN_CORE_H_
#define SYSTEM_RUN_CORE_H_
#include <main.h>
#include <MotorController/motor_controller.h>
#include <EncoderDistance/encoder_distance.h>

class RunCore {
public:
    RunCore();
    ~RunCore();
    void init(MotorController *motorController_, EncoderDistance *currDis_);
    void setVelocity(float vel);
    void moveForward(float dis);
    void spinTurn();

private:
    MotorController *motorController;
    EncoderDistance *currDis;
};

#endif
