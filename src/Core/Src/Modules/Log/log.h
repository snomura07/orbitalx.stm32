#ifndef LOG_H_
#define LOG_H_

#include <main.h>

class Log {
public:
    static constexpr int MAX_SIZE = 1000;

public:
    Log();
    ~Log();
    bool set(int16_t val);
    int16_t getData(uint16_t pickNo);

private:
    int16_t data[MAX_SIZE];
    bool isFull;
    uint16_t index;
};

#endif
