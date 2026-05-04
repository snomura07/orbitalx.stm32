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

int16_t Logger::getLog1(uint16_t pickNo) {
    return log1.getData(pickNo);
}

int16_t Logger::getLog2(uint16_t pickNo) {
    return log2.getData(pickNo);
}

int16_t Logger::getLog3(uint16_t pickNo) {
    return log3.getData(pickNo);
}

int16_t Logger::getLogSize() {
    return log1.MAX_SIZE;
}
