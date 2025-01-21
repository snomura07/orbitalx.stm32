#ifndef SYSTEM_FAIL_SAFE_H_
#define SYSTEM_FAIL_SAFE_H_
#include <main.h>
#include <ObjectHub/object_hub.h>
#include <TimerController/timer_controller.h>

class FailSafe {
public:
    FailSafe();
    ~FailSafe();
    void update();
    void emStopCheck();

private:
    void batteryCheck();

public:
    ObjectHub *objHub;
    TimerController *timer15;
    TimerController *timer6;

private:
    static constexpr float BATTERY_THRE = 3.68;
    bool emStopFlag;
};

#endif
