#include "log.h"

Log::Log():
    isFull(false),
    index(0)
{}

Log::~Log(){}

void Log::set(int16_t val) {
    if(isFull){
        return;
    }

    data[index] = val;
    index++;

    if(index == MAX_SIZE){
        isFull = true;
    }
}
