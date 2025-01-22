#include "timer_count.h"

TimerCount::TimerCount():
    cnt(0)
{
}
TimerCount::~TimerCount(){}

void TimerCount::update(){
    cnt++;
}

void TimerCount::dump(){
    sendMessage("cnt: ");
    sendLong(cnt);
    sendMessage("\r\n");
}
