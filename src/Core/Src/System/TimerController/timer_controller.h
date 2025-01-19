#ifndef SYSTEM_TIMER_CONTROLLER_H_
#define SYSTEM_TIMER_CONTROLLER_H_
#include <main.h>

class TimerController {
public:
    TimerController(TIM_HandleTypeDef &htim_);
    ~TimerController();
    void start();
    void stop();
    bool isStarted();

private:
    TIM_HandleTypeDef *htim;
    bool status;
};

#endif
