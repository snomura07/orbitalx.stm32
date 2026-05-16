#include "calibration.h"
#include <cmath>

Calibration::Calibration(){}
Calibration::~Calibration(){}

void Calibration::init(WallSensor *wallSensor_, LedController *ledController_){
    wallSensor = wallSensor_;
    led        = ledController_;
}

void Calibration::calibrateWallSensorRightSide(){
    led->allOff();
    HAL_Delay(1000);
    led->turnOn(LedController::LedEnum::ORANGE);
    paramPtr->writeWallSensorRefRight(wallSensor->rawData.rFront,
                                      wallSensor->rawData.lFront,
                                      wallSensor->rawData.rSide,
                                      wallSensor->rawData.lSide);
    HAL_Delay(200);
    led->turnOff(LedController::LedEnum::ORANGE);
}

void Calibration::calibrateWallSensorLeftSide(){
    led->allOff();
    HAL_Delay(1000);
    led->turnOn(LedController::LedEnum::ORANGE);
    paramPtr->writeWallSensorRefLeft(wallSensor->rawData.rFront,
                                     wallSensor->rawData.lFront,
                                     wallSensor->rawData.rSide,
                                     wallSensor->rawData.lSide);
    HAL_Delay(200);
    led->turnOff(LedController::LedEnum::ORANGE);
}
