#ifndef SYSTEM_ACTION_ROUTER_H_
#define SYSTEM_ACTION_ROUTER_H_
#include <main.h>
#include <Imu/imu.h>

class ActionLauncher {
private:
    enum ActionEnum {
        SearchRun,
        FastRun,
        Test1,
        Test2,
        Test3,
        Test4,
        Reserve1,
        Reserve2,
        Reserve3,
        Reserve4,
    };

public:
    ActionLauncher(Imu *imu_);
    ~ActionLauncher();
    void select();
    void launch();

private:
    Imu *imu;
    int16_t actionIndex;
};

#endif
