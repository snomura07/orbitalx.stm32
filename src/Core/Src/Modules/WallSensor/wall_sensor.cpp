#include "wall_sensor.h"
#include <main.h>
#include <stm32f3xx_hal.h>

WallSensor::WallSensor(){}

WallSensor::~WallSensor(){}

void WallSensor::turnOnIled(){
    HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_SET);
}

void WallSensor::turnOffIled(){
    HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_RESET);
}

void WallSensor::execAdc(){

}
