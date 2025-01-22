#ifndef TIMER_COUNT_H
#define TIMER_COUNT_H
#include <UsartInterface/usart_interface.h>

class TimerCount : public UsartInterface{
public:
    TimerCount();
    ~TimerCount();
    void update();
    void dump();

public:
    uint32_t cnt;
};

#endif
