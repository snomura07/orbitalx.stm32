#ifndef SYSTEM_LOGGER_H_
#define SYSTEM_LOGGER_H_

#include <memory>
#include <Log/log.h>
#include <UsartInterface/usart_interface.h>

class Logger : public UsartInterface{
public:
    Logger();
    ~Logger();
    void setTimerCnt();
    void setLog1(int16_t val);
    void setLog2(int16_t val);
    void setLog3(int16_t val);
    void activate();
    void deActivate();
    void dump();

private:
    Log log1;
    Log log2;
    Log log3;
    bool isActive;
};

#endif
