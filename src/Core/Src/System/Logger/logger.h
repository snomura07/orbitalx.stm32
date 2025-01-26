#ifndef SYSTEM_LOGGER_H_
#define SYSTEM_LOGGER_H_

#include <memory>
#include <Log/log.h>
#include <TimerCount/timer_count.h>
#include <UsartInterface/usart_interface.h>

class Logger : public UsartInterface{
public:
    Logger();
    ~Logger();
    void setTimerCnt(TimerCount *timerCnt_);
    void setLog1(int16_t val);
    void setLog2(int16_t val);
    void setLog3(int16_t val);
    void dump();

private:
    struct LogSet{
        Log log;
        uint16_t interval;
        uint16_t intervalCnt;
        LogSet() : log(), interval(10), intervalCnt(0) {}
    };
    LogSet log1;
    LogSet log2;
    LogSet log3;

    TimerCount *timerCnt;
};

#endif
