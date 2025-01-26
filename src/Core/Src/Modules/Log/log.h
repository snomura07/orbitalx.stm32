#ifndef LOG_H_
#define LOG_H_

#include <main.h>

class Log{
public:
    Log();
    ~Log();
    void set(int16_t val);
    void dump();

private:
    static constexpr int MAX_SIZE = 1000;
    int16_t data[MAX_SIZE];
    bool isFull;
    uint16_t index;
};

#endif
