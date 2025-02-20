#include "startup.h"
#include <MasterDefine.h>

Startup::Startup(){}
Startup::~Startup(){}

void Startup::run(){
    checkMe();
    checkBattery();
    checkImu();
    checkEncoder();
    checkTimer();
}

void Startup::checkMe(){
    sendMessage("\r\n===== ");
    sendMessage(NAME);
    sendMessage(" ver.");
    sendMessage(VERSION);
    sendMessage(" =====\r\n");
}

void Startup::checkBattery(){
    HAL_Delay(200);
    sendMessage("▼battery \r\n");
    sendMessage("voltage: ");
    sendFloat(objHub->battPtr->volt);
    sendMessage("[V] \r\n");
    sendMessage("voltage: ");
    sendInt(objHub->battPtr->mVolt);
    sendMessage("[mV] \r\n");
    sendMessage("\r\n");
}

void Startup::checkImu(){
    sendMessage("▼IMU \r\n");
    sendMessage("name    : ");
    sendMessage(objHub->imuPtr->getChipName());
    sendMessage("\r\n");
    sendMessage("WHO_AM_I: ");
    sendInt(objHub->imuPtr->whoAmI);
    sendMessage("\r\n\r\n");
}

void Startup::checkEncoder(){
    sendMessage("▼Encoder \r\n");
    sendMessage("right enc raw: ");
    sendInt(objHub->rEncPtr->currRaw);
    sendMessage("\r\n");
    sendMessage("right enc cnt: ");
    sendLong(objHub->rEncPtr->counter);
    sendMessage("\r\n");
    sendMessage("left enc raw: ");
    sendInt(objHub->lEncPtr->currRaw);
    sendMessage("\r\n");
    sendMessage("left enc cnt: ");
    sendLong(objHub->lEncPtr->counter);
    sendMessage("\r\n\r\n");
}

void Startup::checkTimer(){
    sendMessage("▼Timer \r\n");
    sendMessage("timer1[1call/1ms]  : ");
    sendMessage(timer1->isStarted()==true?"started":"stoped");
    sendMessage("\r\n");
    sendMessage("timer15[1call/s]   : ");
    sendMessage(timer15->isStarted()==true?"started":"stoped");
    sendMessage("\r\n");
    sendMessage("timer6 [1call/10ms]: ");
    sendMessage(timer6->isStarted()==true?"started":"stoped");
    sendMessage("\r\n");
    sendMessage("timer7 [1call/10ms]: ");
    sendMessage(timer7->isStarted()==true?"started":"stoped");
    sendMessage("\r\n");
}
