#ifndef SYSTEM_LOGGER_H_
#define SYSTEM_LOGGER_H_

#include <memory>
#include <Log/log.h>

class Logger {
public:
    Logger();
    ~Logger();
    void setTimerCnt();
    void setLog1(int16_t val);
    void setLog2(int16_t val);
    void setLog3(int16_t val);
    int16_t getLog1(uint16_t pickNo);
    int16_t getLog2(uint16_t pickNo);
    int16_t getLog3(uint16_t pickNo);
    void activate();
    void deActivate();
    int16_t getLogSize();

private:
    Log log1;
    Log log2;
    Log log3;
    bool isActive;
};

#endif
