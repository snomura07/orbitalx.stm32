#ifndef TIMER_COUNT_H
#define TIMER_COUNT_H
#include <UtilInterface/util_interface.h>

class TimerCount : public UtilInterface{
public:
    TimerCount();
    ~TimerCount();
    void update();
    void dump();

public:
    uint32_t cnt;
};

#endif
