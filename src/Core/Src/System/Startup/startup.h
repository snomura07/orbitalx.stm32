#ifndef SYSTEM_STARTUP_H_
#define SYSTEM_STARTUP_H_

#include <memory>
#include <ObjectHub/object_hub.h>
#include <UtilInterface/util_interface.h>
#include <TimerController/timer_controller.h>

class Startup : public UtilInterface{
public:
    Startup();
    ~Startup();
    void run();

private:
    void checkMe();
    void checkBattery();
    void checkImu();
    void checkEncoder();
    void checkTimer();

public:
    ObjectHub *objHub;
    TimerController *timer1;
    TimerController *timer15;
    TimerController *timer6;
    TimerController *timer7;
};

#endif
