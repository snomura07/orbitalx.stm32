#ifndef SYSTEM_RUN_CORE_H_
#define SYSTEM_RUN_CORE_H_
#include <main.h>
#include <EncoderDistance/encoder_distance.h>
#include <LedController/led_controller.h>
#include <UtilInterface/util_interface.h>

class RunCore : public UtilInterface {
public:
    RunCore();
    ~RunCore();
    void init(LedController *ledController_,
              EncoderDistance *currDis_);
    void setVelocity(float vel);
    void moveForward(float dis);
    void spinTurn();

private:

    LedController   *ledController;
    EncoderDistance *currDis;
};

#endif
