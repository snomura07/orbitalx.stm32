#ifndef SYSTEM_RUN_CORE_H_
#define SYSTEM_RUN_CORE_H_
#include <main.h>
#include <MotorController/motor_controller.h>
#include <EncoderDistance/encoder_distance.h>
#include <LedController/led_controller.h>
#include <UtilInterface/util_interface.h>

class RunCore : public UtilInterface {
public:
    RunCore();
    ~RunCore();
    void init(MotorController *motorController_,
              LedController *ledController_,
              EncoderDistance *currDis_);
    void setVelocity(float vel);
    void moveForward(float dis);
    void spinTurn();

private:
    MotorController *motorController;
    LedController   *ledController;
    EncoderDistance *currDis;
};

#endif
