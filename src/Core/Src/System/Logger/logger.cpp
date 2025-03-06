#include "logger.h"

Logger::Logger():
    isActive(false)
{}
Logger::~Logger(){}

void Logger::activate() {
    isActive = true;
}

void Logger::deActivate() {
    isActive = false;
}


void Logger::setLog1(int16_t val){
    if(!isActive) return;
    log1.set(val);
}

void Logger::setLog2(int16_t val){
    if(!isActive) return;
    log2.set(val);
}

void Logger::setLog3(int16_t val){
    if(!isActive) return;
    log3.set(val);
}

void Logger::dump(){
    for(int i=0; i<log1.MAX_SIZE; i++){
        sendMessage("[adc]@");
        sendMessage("log1:");
        sendInt(log1.getData(i));
        sendMessage(",");
        sendMessage("log2:");
        sendInt(log2.getData(i));
        sendMessage(",");
        sendMessage("log3:");
        sendInt(log3.getData(i));
        sendMessage("\r\n");
        HAL_Delay(10);
    }
    sendMessage("\r\n");

}
