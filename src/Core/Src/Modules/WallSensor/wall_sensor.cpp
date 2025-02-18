#include "wall_sensor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

WallSensor:: WallSensor(ADC_HandleTypeDef &hadc1_, ADC_HandleTypeDef &hadc2_):
    hadc1(&hadc1_),
    hadc2(&hadc2_),
    sensor1(0),
    sensor2(0)
{}
WallSensor::~WallSensor(){}

void WallSensor::update(){
    turnOnIled();
    HAL_Delay(10);

    // ADC1_4 の変換
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_4;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    HAL_ADC_ConfigChannel(hadc1, &sConfig);
    HAL_ADC_Start(hadc1);
    HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);
    sensor1 = HAL_ADC_GetValue(hadc1);
    HAL_ADC_Stop(hadc1);

    // ADC2_1 の変換
    sConfig.Channel = ADC_CHANNEL_1;
    HAL_ADC_ConfigChannel(hadc2, &sConfig);
    HAL_ADC_Start(hadc2);
    HAL_ADC_PollForConversion(hadc2, HAL_MAX_DELAY);
    sensor2 = HAL_ADC_GetValue(hadc2);
    HAL_ADC_Stop(hadc2);

    turnOffIled();
}

void WallSensor::turnOnIled(){
    // HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_SET);
}

void WallSensor::turnOffIled(){
    // HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_RESET);
}

void WallSensor::dump(){
    sendMessage("sens1:");
    sendInt(sensor1);
    sendMessage(", ");
    sendMessage("sens2:");
    sendInt(sensor2);
    sendMessage("\r\n");
}
