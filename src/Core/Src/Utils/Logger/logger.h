#ifndef UTILS_LOGGER_H_
#define UTILS_LOGGER_H_

#include <main.h>

class Logger{
public:
    Logger(uint16_t interval_=10);
    ~Logger();

private:
    static constexpr int MAX_SIZE = 1000;
    int16_t data[MAX_SIZE];
    uint16_t interval;
};

#endif
