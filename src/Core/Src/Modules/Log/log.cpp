#include "log.h"
#include <cstring>

Log::Log():
    isFull(false),
    index(0)
{
    memset(data, 0, sizeof(data));
}

Log::~Log(){}

bool Log::set(int16_t val) {
    if(isFull){
        return false;
    }

    data[index] = val;
    index++;

    if(index == MAX_SIZE){
        isFull = true;
    }
    return true;
}

int16_t Log::getData(uint16_t pickNo) {
    if(pickNo < MAX_SIZE && pickNo >= 0){
        return data[pickNo];
    }
    else {
        return -1;
    }
}
