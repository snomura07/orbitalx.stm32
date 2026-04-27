#include "zupt.h"
#include <cmath>

Zupt::Zupt():
    status(StatusEnum::STOPPED),
    zuptCnt(0)
{}
Zupt::~Zupt(){}

void Zupt::init(EncoderDistance *encoderDistance_, Imu *imu_, Led *redLed_){
    encoderDistance = encoderDistance_;
    imu             = imu_;
    redLed          = redLed_;
}

// 1ms周期でupdateされる前提の処理
void Zupt::update(){

    //evaluate gyro z
    // int16_t cGyroZ = abs(imu->gyroCorrected.z);
    // if(cGyroZ < 100){
    //     zuptCnt++;
    // }
    // else{
    //     zuptCnt = 0;
    //     status  = StatusEnum::MOVED;
    // }

    //evaluate encoder dis
    if(encoderDistance->deltaMm < 5){
        zuptCnt++;
    }
    else{
        zuptCnt = 0;
        status  = StatusEnum::MOVED;
    }

    //status check
    if(zuptCnt > 200){
        status  = StatusEnum::STOPPED;
        zuptCnt = 0;
        imu->setZeroPoint();
    }

    //output
    if(isStopped()){
        redLed->on();
    }
    else{
        redLed->off();
    }
}

bool Zupt::isStopped(){
    return status==StatusEnum::STOPPED;
}

void Zupt::dump(){
    sendMessage("[ZUPT] ");
    sendMessage("gyroZ: ");
    sendInt(imu->gyroCorrected.z);
    sendMessage(", accelY: ");
    sendInt(imu->accelCorrected.y);
    sendMessage(", zuptCnt: ");
    sendInt(zuptCnt);
    sendMessage("\r\n");
}
