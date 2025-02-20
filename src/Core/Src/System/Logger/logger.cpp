#include "logger.h"

Logger::Logger(){}
Logger::~Logger(){}

void Logger::setTimerCnt(TimerCount *timerCnt_) {
    timerCnt = timerCnt_;
}

void Logger::setLog1(int16_t val){
    if((timerCnt->cnt - log1.intervalCnt) >= log1.interval){
        log1.log.set(val);
        log1.intervalCnt = timerCnt->cnt;
    }
}

void Logger::setLog2(int16_t val){
    if((timerCnt->cnt - log2.intervalCnt) >= log2.interval){
        log2.log.set(val);
        log2.intervalCnt = timerCnt->cnt;
    }
}

void Logger::setLog3(int16_t val){
    if((timerCnt->cnt - log3.intervalCnt) >= log3.interval){
        log3.log.set(val);
        log3.intervalCnt = timerCnt->cnt;
    }
}

void Logger::dump(){
    for(int i=0; i<log1.log.MAX_SIZE; i++){
        sendMessage("[adc]@");
        sendInt(log1.log.getData(i));
        sendMessage(",");
        sendInt(log2.log.getData(i));
        sendMessage("\r\n");
        HAL_Delay(5);
    }
    sendMessage("\r\n");

}
