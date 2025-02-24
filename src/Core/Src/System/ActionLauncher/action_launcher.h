#ifndef SYSTEM_ACTION_ROUTER_H_
#define SYSTEM_ACTION_ROUTER_H_
#include <main.h>
#include <Imu/imu.h>
#include <LedController/led_controller.h>
#include <WallSensor/wall_sensor.h>

class ActionLauncher {
private:
    enum ActionEnum {
        SearchRun,
        FastRun,
        Test1,
        Test2,
        Test3,
        Test4,
        EnumSize,
    };

public:
    ActionLauncher();
    ~ActionLauncher();
    void init(Imu *imu_, LedController *ledController_, WallSensor *wallSensor_);
    void select();
    void launch();

private:
    void standbyStay();

private:
    Imu *imu;
    LedController *ledController;
    WallSensor *wallSensor;
    int16_t actionIndex;
};

#endif
