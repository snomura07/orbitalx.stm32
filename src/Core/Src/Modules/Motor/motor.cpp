#include "motor.h"
#include <main.h>
#include <stm32g4xx_hal.h>

Motor::Motor(TIM_HandleTypeDef &htim_, ModeEnum mode_):
    htim(&htim_),mode(mode_)
{}

Motor::~Motor(){}

void Motor::start(){
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
}

void Motor::stop(){
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, 1);
    HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_2);
}

void Motor::setDuty(uint16_t duty){
    if(mode == LEFT){
	  HAL_GPIO_WritePin(MOTA_IN1_GPIO_Port, MOTA_IN1_Pin, GPIO_PIN_RESET);
    }
    if(mode == RIGHT){
	  HAL_GPIO_WritePin(MOTB_IN1_GPIO_Port, MOTB_IN1_Pin, GPIO_PIN_SET);
    }

    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, duty);
}
